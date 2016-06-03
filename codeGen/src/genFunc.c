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
	FreeReg(REG_RAX);
	instrMOV_VAL_REG(BYTE_8, 0, reg_pool[REG_RAX].reg_name);
	asmPrintf_func("    call    %s\n\n", get_tkSTR(opTop->sym->tk_code));
	operand_pop();
}

