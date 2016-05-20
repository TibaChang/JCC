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

#include "global_var.h"
#include "token.h"

/*Lexical analysis*/
tkWord *tk_hashTable[MAX_KEY];
dynARR tkTable;
dynSTR sourceSTR;
dynSTR cur_tkSTR;
int tkValue;
TOKEN cur_token;
uint32_t compiler_stage;
uint32_t cur_line_num;
char *cur_filename;
char cur_CHAR;
FILE *cur_File;


/*Syntax analysis*/
uint32_t syntax_state;
uint32_t syntax_indent_level;


