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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "lex.h"
#include "global_var.h"
#include "token.h"
#include "jcc.h"
#include "declaration.h"
#include "stack.h"
#include "symbol.h"

int main(int argc, char **argv)
{
	cur_File = fopen(argv[1], "r");
	if (!cur_File) {
		printf("Opening JCC source file failed!\n");
		return -1;
	}
	cur_filename = argv[1];

	init();

	getCHAR();
	getToken();
	translation_unit();

	cleanup();
	fclose(cur_File);
	printf("Semantic Analysis SUCCESS! File: %s \n\n", argv[1]);
	return 0;
}

void init(void)
{
	cur_line_num = 1;
	init_lex();

	stack_init(&local_sym_stack, 8);
	stack_init(&global_sym_stack, 8);
	sym_sec_rdata = sec_sym_put(".rdata", 0);

	int_type.data_type = T_INT;
	char_pointer_type.data_type = T_CHAR;
	mk_pointer(&char_pointer_type);
	default_func_type.data_type = T_FUNC;
	default_func_type.ref = sym_push(JC_ANOM, &int_type, NOT_SPECIFIED, NOT_SPECIFIED);
}

void cleanup(void)
{
	printf("\ntkTable.count = %d \n", tkTable.count);

	sym_pop(&global_sym_stack, NULL);
	stack_destroy(&local_sym_stack);
	stack_destroy(&global_sym_stack);

	for (TOKEN i = tk_IDENT; i < tkTable.count; i++) {
		free(tkTable.data[i]);
	}
	free(tkTable.data);
}





