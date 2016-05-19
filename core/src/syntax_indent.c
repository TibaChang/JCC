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

#include <stdint.h>
#include "syntax_indent.h"
#include "global_var.h"
#include "jcc.h"

static void print_tab(uint32_t tab_num)
{
	for (uint32_t i = 0; i < tab_num; i++) {
		printf("\t");
	}
}


void syntax_indent(void)
{
	switch (syntax_state) {
	case SNTX_NUL:
		color_token(LEX_NORMAL);
		break;
	case SNTX_SP:
		printf(" ");
		color_token(LEX_NORMAL);
		break;
	case SNTX_NL_ID:
		if (cur_token == tk_END) {
			syntax_indent_level--;
		}
		printf("\n");
		print_tab(syntax_indent_level);

		color_token(LEX_NORMAL);
		break;
	case SNTX_DELAY:
		break;
	}
	syntax_state = SNTX_NUL;
}

