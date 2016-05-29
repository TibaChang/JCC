/*
 * Copyright (c) 2016, Chang Jia-Rung, All Rights Reserved
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <string.h>
#include "genFunc.h"
#include "genVar.h"
#include "token.h"
#include "exception.h"
#include "symbol.h"
#include "funcArg.h"
#include "genInstr.h"
#include "var_storage.h"
#include "global_var.h"

void setFuncConstValFlag(void)
{
	FuncConstValFlag = FuncIsPassingConstVal;
}

void clearFuncConstValFlag(void)
{
	FuncConstValFlag = FuncNotPassingConstVal;
}

uint32_t isFuncPassConstVal(void)
{
	if (FuncConstValFlag == FuncIsPassingConstVal) {
		return FuncIsPassingConstVal;
	} else {
		return FuncNotPassingConstVal;
	}
}


void genFileTitle(FILE * file, char *file_name)
{
	fprintf(file, ".file   \"%s\"\n\n\n", file_name);
}


void genFuncProlog(Symbol *sym)
{
	char *func_name = get_tkSTR(sym->tk_code & JC_ValMASK);
	asmPrintf("\n    .text\n");
	asmPrintf("    .globl  %s\n", func_name);
	asmPrintf("    .type   %s, @function\n", func_name);
	asmPrintf("%s:\n", func_name);
	asmPrintf("    pushq   %%rbp\n");
	asmPrintf("    movq    %%rsp, %%rbp\n\n");
}


void genFuncEpilog(Symbol *sym)
{
	char *func_name = get_tkSTR(sym->tk_code & JC_ValMASK);
	if (strncmp("main", func_name, 4) == 0) { /*if this is main function*/
		asmPrintf("\n    leave\n");
	} else {
		asmPrintf("    popq    %%rbp\n");
	}
	asmPrintf("    ret\n");
	asmPrintf("    .size   %s, .-%s\n\n", func_name, func_name);
}



static void calcFuncParaNum(Symbol *sym)
{
	Symbol *s;
	uint32_t para_count = 0;
	for (s = sym->type.ref->next; s != NULL ; s = s->next) {
		para_count++;
	}
	set_CodeGenStatus(FuncParaNum, para_count);
}


static void add_FuncPara(Symbol *sym)
{
	if (sym->type.data_type == T_FUNC) {
		char FuncName[31];
		memset(FuncName, '\0', 31);
		strncpy(FuncName, get_tkSTR(sym->tk_code), strlen(get_tkSTR(sym->tk_code)));
		FuncArgs_push(FuncName, NOT_SPECIFIED, NOT_SPECIFIED, strlen(get_tkSTR(sym->tk_code)), NOT_SPECIFIED, NOT_SPECIFIED);
	} else {
		if (sym->storage_type & JC_GLOBAL) {
			char GlobalVar_name[31];
			strncpy(GlobalVar_name, get_tkSTR(sym->tk_code), strlen(get_tkSTR(sym->tk_code)));
			FuncArgs_push(NOT_SPECIFIED, sym->storage_type & 0x13, GlobalVar_name, strlen(get_tkSTR(sym->tk_code)), sym->fp_offset, &sym->relation);
		} else if (sym->storage_type & JC_LOCAL) {
			FuncArgs_push(NOT_SPECIFIED, sym->storage_type & 0x13, NOT_SPECIFIED, NOT_SPECIFIED, sym->fp_offset , &sym->relation);
		} else if (sym->storage_type & JC_CONST) {
			FuncArgs_push(NOT_SPECIFIED, sym->storage_type & 0x13, NOT_SPECIFIED, NOT_SPECIFIED, NOT_SPECIFIED, &sym->relation);
		} else {
			error("Variable scope error!");
		}
		FuncParaIndex++;
	}
}

static void genFuncCallAsm(void)
{

	FuncArgs *args = FuncArgs_getTop();
	uint32_t scope, value, size, index = 1;
	char dest_reg[4], src_reg[4];

	/*if funcName equal to PARAMETER, then this is parameter*/
	while (strncmp(args->funcName, PARAMETER, strlen(PARAMETER)) == 0) {
		scope = args->arg_scope;
		value = *((uint32_t*)args->value_ref);

		/*JCC all use 8-bytes regs*/
		size = 8;

		switch (index) {
		case 1:
			strncpy(dest_reg, "rdx", 3);
			break;
		case 2:
			strncpy(dest_reg, "rsi", 3);
			break;
		case 3:
			strncpy(dest_reg, "rdi", 3);
			break;
		case 4:
			strncpy(dest_reg, "rcx", 3);
			break;
		default:
			error("JCC does not support more than 4 arguments!");
			break;
		}

		switch (scope) {
		case JC_GLOBAL:
			strncpy(src_reg, "rip", 3);
			instrMOV_symOFFSET_REG(size, args->global_name, src_reg, dest_reg);
			break;
		case JC_LOCAL:
			strncpy(src_reg, "rbp", 3);
			instrMOV_OFFSET_REG(size, src_reg, dest_reg, args->fp_offset);
			break;
		case JC_CONST:
			instrMOV_VAL_REG(size, value, dest_reg);
			break;
		default:
			error("argument scope error!");
			break;
		}

		FuncArgs_pop();
		args = FuncArgs_getTop();
		index++;
	}
	args = FuncArgs_getTop();
	asmPrintf("    call    %s\n", args->funcName);
}


void genFuncCall(Symbol *sym)
{
	Symbol s;

	if (sym->type.data_type == T_FUNC) {
		set_CodeGenStatus(FuncParaAccept, NOT_SPECIFIED);
		calcFuncParaNum(sym);
		add_FuncPara(sym);
		return;
	}
	if (isFuncPassConstVal() == FuncIsPassingConstVal) {
		//if we pass const int/char, the sym will be NULL
		sym = &s;
		sym->storage_type = JC_CONST;
		sym->relation = tkValue;
	}

	if (CodeGenStatus == FuncParaAccept) {
		add_FuncPara(sym);
		if (FuncPara_count == FuncParaIndex) {
			set_CodeGenStatus(FuncParaClear, NOT_SPECIFIED);
			genFuncCallAsm();
		}
	}
}

