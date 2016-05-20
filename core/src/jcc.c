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

	printf("  Total code line number: %d lines\n", cur_line_num);

	cleanup();
	fclose(cur_File);
	printf("Syntax Analysis SUCCESS! File: %s \n", argv[1]);
	return 0;
}

void init(void)
{
	cur_line_num = 1;
	init_lex();
}

void cleanup(void)
{
	printf("tkTable.count = %d \n", tkTable.count);

	for (TOKEN i = tk_IDENT; i < tkTable.count; i++) {
		free(tkTable.data[i]);
	}
	free(tkTable.data);
}


#define C_NORMAL      "\x1B[0m"
#define C_RED         "\x1B[31;1m"
#define C_GREEN       "\x1B[32;1m"
#define C_YELLOW      "\x1B[33;1m"
#define C_BLUE        "\x1B[34;1m"
#define C_MAGENTA     "\x1B[35;1m"
#define C_CYAN        "\x1B[36;1m"
#define C_WHILE_DARK  "\x1B[37;1m"

void color_token(int lex_state)
{
	switch (lex_state) {
	case LEX_NORMAL: {
			if (cur_token >= tk_IDENT) {
				printf("%s", C_CYAN);
			} else if (cur_token >= kw_CHAR) {
				printf("%s", C_GREEN);
			} else if (cur_token >= tk_cINT) {
				printf("%s", C_YELLOW);
			} else {
				printf("%s", C_WHILE_DARK);
			}

			printf("%s", get_tkSTR(cur_token));
			break;
		}
	case LEX_SEPARATOR: {
			printf("%c", cur_CHAR);
			break;
		}
	}
}



