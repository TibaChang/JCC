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
#include "funcArg.h"
#include "stack.h"
#include "global_var.h"
#include <string.h>
#include "symbol.h"

FuncArgs *FuncArgs_push(char *funcName, uint32_t arg_scope, char *global_name, uint32_t global_name_len, int offset, void *value)
{
	FuncArgs args, *p;
	if (funcName != NOT_SPECIFIED) {
		strcpy(args.funcName, funcName);
	} else {
		strncpy(args.funcName, PARAMETER, strlen(PARAMETER));
	}

	if (global_name != NOT_SPECIFIED) {
		strncpy(args.global_name, global_name, global_name_len);
	}
	args.arg_scope = arg_scope;
	args.fp_offset = offset;
	args.value_ref = value;
	p = (FuncArgs*)stack_push(&FuncArg_stack, &args, sizeof(FuncArgs));
	return p;
}


FuncArgs *FuncArgs_getTop(void)
{
	return (FuncArgs*)stack_get_top(&FuncArg_stack);
}

void FuncArgs_pop(void)
{
	stack_pop(&FuncArg_stack);
}

