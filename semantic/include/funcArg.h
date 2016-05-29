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
#ifndef __FUNC_ARG_H
#define __FUNC_ARG_H

#include <stdint.h>

#define PARAMETER       "%%%%parameter"
#define NOT_GLOBAL_VAR  "%%%%NOT_GLOBAL_VAR"

typedef struct {
	char funcName[31];/*for parameter,this will be NULL*/
	uint32_t arg_scope;/*local/global*/
	char global_name[31];/*for global variable*/
	int fp_offset;/*for local variable*/
	void *value_ref;
} FuncArgs;

FuncArgs *FuncArgs_push(char *funcName, uint32_t arg_scope, char *global_name, uint32_t global_name_len, int offset, void *value);
FuncArgs *FuncArgs_getTop(void);
void FuncArgs_pop(void);

#endif

