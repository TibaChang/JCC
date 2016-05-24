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

#ifndef __SYMBOL_H_
#define __SYMBOL_H_
#include <stdint.h>
#include "stack.h"
#include "token.h"

/*Storage type*/
#define	 JC_GLOBAL   0x00F0  /*const. int/char/string/global var/function def  */
#define  JC_LOCAL    0x00F1  /*local var in stack*/
#define  JC_LLOCAL   0x00F2  /*register overflow to put in stack*/
#define  JC_CMP      0x00F3  /*Using FLAG registers*/
#define	 JC_ValMASK  0x00FF
#define  JC_LVAL     0x0100  /*lvalue*/
#define  JC_SYM      0x0200  /*symbol*/

/*Symbol type*/
#define  JC_ANOM     0x10000000/*anonymous symbol*/
#define  JC_STRUCT   0x20000000/*struct symbol*/
#define  JC_MEMBER   0x40000000/*struct member*/
#define  JC_PARAMS   0x80000000/*function parameters*/

/*Type code*/
#define  T_INT     0
#define	 T_CHAR    1
#define	 T_VOID    2
#define	 T_PTR     3
#define	 T_FUNC    4
#define	 T_STRUCT  5

#define	 T_BTYPE   0x000F /*base type mask:"int" to "struct"*/
#define	 T_ARRAY   0x0010

/*sym_push code*/
#define NOT_SPECIFIED        0
#define STRUCT_NOT_DEFINED  -1
#define PTR_NOT_DEFINED     -1
#define NOT_DEFINED         -1


typedef struct Type {
	uint32_t data_type;
	struct Symbol *ref;
} Type;

typedef struct Symbol {
	TOKEN tk_code;       /*token encoding,v*/
	uint32_t storage_type;        /*symbol register,r,reg,FIXME:name: scope,struct_align,func_call(JCC not support) */
	int relation;           /*symbol realation value,c,value,FIXME:name: struct_size,struct_offset, -1 for not defined,tkValue, */
	struct Type type;    /*symbol type*/
	struct Symbol *next; /*pointer to relavent symbol,ex: struct member declaration list,in struct_declaration()*/
	struct Symbol *prev; /*pointer to previous symbol with same name,ex:base type of the struct will point to itself*/
} Symbol;


Symbol *sym_direct_push(Stack *ss, uint32_t modified_tk, Type *type, int relation);
Symbol *sym_push(uint32_t modified_tk, Type *type, uint32_t storage_type, int relation);
Symbol *func_sym_push(uint32_t tk, Type *type);
Symbol *var_sym_put(Type *type, uint32_t storage_type, TOKEN tk, int addr);
Symbol *sec_sym_put(char *sec, int relation);
void sym_pop(Stack *stack, Symbol *sym);
Symbol *struct_search(TOKEN tk);
Symbol *sym_search(TOKEN tk);


#endif

