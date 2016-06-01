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
#define	 JC_GLOBAL   0x0001  /*const. int/char/string/global var/function def  */
#define  JC_LOCAL    0x0002  /*local var in stack*/
#define  JC_LLOCAL   0x0004  /*register overflow to put in stack*/
#define  JC_CMP      0x0008  /*Using FLAG registers*/
#define	 JC_ValMASK  0x00FF
#define  JC_LVAL     0x0100  /*lvalue*/
#define  JC_SYM      0x0200  /*symbol*/
#define  JC_CONST    0x0010  /*pass a const value to function*/
#define  JC_RET_REG  0xF000

/*Symbol type(with tk_code)*/
#define  JC_ANOM        0x10000000/*anonymous symbol*/
#define  JC_STRUCT      0x20000000/*struct symbol*/
#define  JC_MEMBER      0x40000000/*struct member*/
#define  JC_PARAMS      0x80000000/*function parameters*/
#define  JC_SymTypeMASK 0xF0000000

/*Type code*/
#define  T_INT      0
#define	 T_CHAR     1
#define	 T_VOID     2
#define	 T_PTR      3
#define	 T_FUNC     4
#define	 T_STRUCT   5
#define	 T_BTYPE    0x000F /*base type mask:"int" to "struct"*/
#define	 T_ARRAY    0x0010
#define  T_NOT_TYPE 0xFFFF

/*sym_push code*/
#define NOT_SPECIFIED        0
#define STRUCT_NOT_DEFINED  -1
#define PTR_NOT_DEFINED     -1
#define NOT_DEFINED         -1
#define VAR_NOT_INIT         0
#define VAR_HAS_INIT         1


typedef struct Type {
	uint32_t data_type;
	struct Symbol *ref;
} Type;

typedef struct Symbol {
	uint32_t tk_code;     /*token encoding,v*/
	uint32_t storage_type;/*scope / struct_align(JC_STRUCT)  */
	int relation;         /*struct_size / struct_offset(JC_MEMBER) / -1 for not defined / tkValue / const string:symbol number */
	int fp_offset;   /*local variable: fp offset */
	struct Type type;     /*symbol type*/
	struct Symbol *next;  /*pointer to relavent symbol,ex: struct member declaration list,in struct_declaration()*/
	struct Symbol *prev;  /*pointer to previous symbol with same name,ex:base type of the struct will point to itself*/
} Symbol;


Symbol *sym_direct_push(Stack *ss, uint32_t modified_tk, Type *type, int relation);
Symbol *sym_push(uint32_t modified_tk, Type *type, uint32_t storage_type, int relation);
Symbol *func_sym_push(uint32_t tk, Type *type);
Symbol *var_sym_put(Type *type, uint32_t storage_type, uint32_t tk, int addr);
Symbol *sec_sym_put(char *sec, int relation);
void sym_pop(Stack *stack, Symbol *sym);
Symbol *struct_search(uint32_t tk);
Symbol *sym_search(uint32_t tk);


#endif

