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
	asmPrintf("    movq    %%rsp, %%rbp\n");
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

