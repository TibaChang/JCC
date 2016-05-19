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

#ifndef __GLOBAL_VAR_H
#define __GLOBAL_VAR_H

#include <stdint.h>
#include <stdio.h>
#include "token.h"
#include "tkWord_Hash.h"
#include "dynARR.h"
#include "dynSTR.h"

/*Lexcial analysis*/
extern tkWord *tk_hashTable[MAX_KEY];
extern dynARR tkTable;
/*In get_tkSTR(),if the target token is constant string/character/number, we get string from dynSTR sourceSTR */
extern dynSTR sourceSTR;
/* For identifying (new) token purpose. */
extern dynSTR cur_tkSTR;
extern int tkValue;
extern TOKEN cur_token;
extern uint32_t compiler_stage;
extern uint32_t cur_line_num;
/*Indicating where are we in the JCC source file.*/
extern char cur_CHAR;
/*The target JCC source file*/
extern FILE *cur_File;
extern char *cur_filename;
/**************************************************************/


/*Syntax analysis*/
typedef enum {
	SNTX_NUL,   /* No indent behavior */
	SNTX_SP,    /* space */
	SNTX_NL_ID, /* New Line and InDent,for every declaration,function definition and end of statement */
	SNTX_DELAY  /* Confirm the format until the next word */
} SyntaxState;

typedef enum {
	JC_GLOBAL = 0x00f0,
	JC_LOCAL  = 0x00f1,
	/*FIXME:struct member
	 * There will be more definition here.
	 **/
	JC_ANOM   = 0x10000000,
	JC_STRUCT = 0x20000000,
	JC_MEMBER = 0x40000000,
	JC_PARAMS = 0x80000000,
} StorageClass;

extern uint32_t syntax_state;
extern uint32_t syntax_indent_level;

/**************************************************************/

#endif
