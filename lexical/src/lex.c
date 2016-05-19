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
#include "lex.h"
#include "global_var.h"
#include "token.h"
#include "tkWord_Hash.h"
#include "exception.h"
#include "dynARR.h"

void init_lex(void)
{
	static tkWord keywords[] = {
		{tk_PLUS,      NULL,   "+",                strlen("+")},
		{tk_MINUS,     NULL,   "-",                strlen("-")},
		{tk_STAR,      NULL,   "*",                strlen("*")},
		{tk_DIVIDE,    NULL,   "/",                strlen("/")},
		{tk_MOD,       NULL,   "%",                strlen("%")},
		{tk_EQ,        NULL,   "==",               strlen("==")},
		{tk_NEQ,       NULL,   "!=",               strlen("!=")},
		{tk_LT,        NULL,   "<",                strlen("<")},
		{tk_LEQ,       NULL,   "<=",               strlen("<=")},
		{tk_GT,        NULL,   ">",                strlen(">")},
		{tk_GEQ,       NULL,   ">=",               strlen(">=")},
		{tk_ASSIGN,    NULL,   "=",                strlen("=")},
		{tk_POINTTO,   NULL,   "->",               strlen("->")},
		{tk_DOT,       NULL,   ".",                strlen(".")},
		{tk_AND,       NULL,   "&",                strlen("&")},
		{tk_openPA,    NULL,   "(",                strlen("(")},
		{tk_closePA,   NULL,   ")",                strlen(")")},
		{tk_openBR,    NULL,   "[",                strlen("[")},
		{tk_closeBR,   NULL,   "]",                strlen("]")},
		{tk_BEGIN,     NULL,   "{",                strlen("{")},
		{tk_END,       NULL,   "}",                strlen("}")},
		{tk_SEMICOLON, NULL,   ";",                strlen(";")},
		{tk_COMMA,     NULL,   ",",                strlen(",")},
		{tk_ELLIPSIS,  NULL,   "...",              strlen("...")},
		{tk_EOF,       NULL,   "End_Of_File",      strlen("End_Of_File")},

		{tk_cINT,      NULL,   "Constant Integer", strlen("Constant Integer")},
		{tk_cCHAR,     NULL,   "Constant CHAR",    strlen("Constant CHAR")},
		{tk_cSTR,      NULL,   "Constant String",  strlen("Constant String")},

		{kw_CHAR,      NULL,   "char",             strlen("char")},
		{kw_INT,       NULL,   "int",              strlen("int")},
		{kw_VOID,      NULL,   "void",             strlen("void")},
		{kw_STRUCT,    NULL,   "struct",           strlen("struct")},

		{kw_IF,        NULL,   "if",               strlen("if")},
		{kw_ELSE,      NULL,   "else",             strlen("else")},
		{kw_FOR,       NULL,   "for",              strlen("for")},
		{kw_CONTINUE,  NULL,   "continue",         strlen("continue")},
		{kw_BREAK,     NULL,   "break",            strlen("break")},
		{kw_RETURN,    NULL,   "return",           strlen("return")},
		{kw_SIZEOF,    NULL,   "sizeof",           strlen("sizeof")},

		/*For the foe loop below*/
		{0,           NULL,   NULL,          0}
	};

	dynARR_init(&tkTable, 8);
	for (tkWord *tkp = &keywords[0]; tkp->str != NULL; tkp++) {
		tkW_direct_insert(tkp);
	}
}



