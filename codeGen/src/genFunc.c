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
#include <stdlib.h>
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


void genFileTitle(void)
{
	asmPrintf(".file   \"%s\"\n\n\n", cur_filename);
}


void genFuncProlog(Symbol *sym)
{
	char *func_name = get_tkSTR(sym->tk_code & JC_ValMASK);
	asmPrintf_func("\n    .text\n");
	asmPrintf_func("    .globl  %s\n", func_name);
	asmPrintf_func("    .type   %s, @function\n", func_name);
	asmPrintf_func("%s:\n", func_name);
	asmPrintf_func("    pushq   %%rbp\n");
	asmPrintf_func("    movq    %%rsp, %%rbp\n\n");
}


void genFuncEpilog(Symbol *sym)
{
	char *func_name = get_tkSTR(sym->tk_code & JC_ValMASK);
	if (strcmp("main", func_name) == 0) { /*if this is main function*/
		asmPrintf_func("\n    leave\n");
	} else {
		asmPrintf_func("    popq    %%rbp\n");
	}
	asmPrintf_func("    ret\n");
	asmPrintf_func("    .size   %s, .-%s\n\n", func_name, func_name);
}



static void add_FuncPara(Symbol *sym)
{
	if (sym->type.data_type == T_FUNC) {
		char FuncName[31];
		memset(FuncName, '\0', 31);
		strcpy(FuncName, get_tkSTR(sym->tk_code));
		FuncArgs_push(FuncName, NOT_SPECIFIED, NOT_SPECIFIED, NOT_SPECIFIED, NOT_SPECIFIED);
	} else {
		if (sym->storage_type & JC_GLOBAL) {
			char GlobalVar_name[31];
			strcpy(GlobalVar_name, get_tkSTR(sym->tk_code));
			FuncArgs_push(NOT_SPECIFIED, sym->storage_type & 0x13, GlobalVar_name, sym->fp_offset, sym->relation);
		} else if (sym->storage_type & JC_LOCAL) {
			FuncArgs_push(NOT_SPECIFIED, sym->storage_type & 0x13, NOT_SPECIFIED, sym->fp_offset , sym->relation);
		} else if (sym->storage_type & JC_CONST) {
			FuncArgs_push(NOT_SPECIFIED, sym->storage_type & 0x13, NOT_SPECIFIED, NOT_SPECIFIED, sym->relation);
		} else {
			error("Variable scope error!");
		}
		FuncParaIndex++;
	}
}

static void genFuncCallAsm(void)
{

	FuncArgs *args = FuncArgs_getTop();
	uint32_t scope,  size, index, count;
	uint64_t value;
	char dest_reg[4], src_reg[4];

	index = 0;
	/*if funcName equal to PARAMETER, then this is parameter*/
	while (strcmp(args->funcName, PARAMETER) == 0) {
		scope = args->arg_scope;
		value = args->value;
		count = FuncPara_count - index;

		/*JCC all use 8-bytes regs*/
		size = 8;

		switch (count) {
		case 1:
			strcpy(dest_reg, "rdi");
			break;
		case 2:
			strcpy(dest_reg, "rsi");
			break;
		case 3:
			strcpy(dest_reg, "rdx");
			break;
		case 4:
			strcpy(dest_reg, "rcx");
			break;
		default:
			error("JCC does not support more than 4 arguments!");
			break;
		}

		switch (scope) {
		case JC_GLOBAL:
			strcpy(src_reg, "rip");
			instrMOV_symOFFSET_REG(size, args->global_name, src_reg, dest_reg);
			break;
		case JC_LOCAL:
			strcpy(src_reg, "rbp");
			instrMOV_OFFSET_REG(size, src_reg, dest_reg, args->fp_offset);
			break;
		case JC_CONST:
			instrMOV_VAL_REG(size, value, dest_reg);
			break;
		default:
			interERROR("argument scope error!");
			break;
		}

		FuncArgs_pop();
		args = FuncArgs_getTop();
		index++;
	}
	args = FuncArgs_getTop();
	asmPrintf_func("    call    %s\n\n", args->funcName);
}


void genFuncCall(uint32_t argc)
{
	char dest_reg[4];
	for (int i = argc; i > 0; i--) {
		switch (i) {
		case 4:/*arg 4*/
			FreeReg(REG_RCX);
			strcpy(dest_reg, reg_pool[REG_RCX].reg_name);
			assignReg(REG_RCX);
			reg_pool[REG_RCX].usage |= REG_WILL_USE;
			break;
		case 3:/*arg 3*/
			FreeReg(REG_RDX);
			strcpy(dest_reg, reg_pool[REG_RDX].reg_name);
			assignReg(REG_RDX);
			reg_pool[REG_RDX].usage |= REG_WILL_USE;
			break;
		case 2:/*arg 2*/
			FreeReg(REG_RSI);
			strcpy(dest_reg, reg_pool[REG_RSI].reg_name);
			assignReg(REG_RSI);
			reg_pool[REG_RSI].usage |= REG_WILL_USE;
			break;
		case 1:/*arg 1*/
			FreeReg(REG_RDI);
			strcpy(dest_reg, reg_pool[REG_RDI].reg_name);
			assignReg(REG_RDI);
			reg_pool[REG_RDI].usage |= REG_WILL_USE;
			break;
		default:
			error("JCC only suppory at most 4 arguments!");
			break;
		}
	}

	/*printf does not need function defintion,so we need to free the reg status manually*/
	if (strcmp(get_tkSTR(opTop->sym->tk_code), "printf") == 0) {
		for (int i = argc; i > 0; i--) {
			switch (i) {
			case 4:/*arg 4*/
				setReg_Unused(REG_RCX);
				break;
			case 3:/*arg 3*/
				setReg_Unused(REG_RDX);
				break;
			case 2:/*arg 2*/
				setReg_Unused(REG_RSI);
				break;
			case 1:/*arg 1*/
				setReg_Unused(REG_RDI);
				break;
			}
		}
	}

	asmPrintf_func("    call    %s\n\n", get_tkSTR(opTop->sym->tk_code));
	operand_pop();
}

