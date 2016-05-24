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
#include "expression.h"
#include "declaration.h"
#include "global_var.h"
#include "token.h"
#include "exception.h"
#include "lex.h"
#include "statement.h"


/**************************************************
 * <expression>::=<assignment_expression>{<tk_COMMA><assignment_expression>}
 **************************************************/
void expression(void)
{
	while (1) {
		assignment_expression();
		if (cur_token != tk_COMMA) {
			break;
		}
		getToken();
	}
}


/**************************************************
 * <assignment_expression>::=<equality_expression>
 *                         | <unary_expression><tk_ASSIGN><assignment_expression>
 *
 * We modified the grammar into:
 *
 * <assignment_expression>::=<equality_expression>{<tk_ASSIGN><assignment_expression>}
 **************************************************/
void assignment_expression(void)
{
	equality_expression();
	if (cur_token == tk_ASSIGN) {
		getToken();
		assignment_expression();
	}
}


/**************************************************
 * <equality_expression>::=<relational_expression>
 *                       { <tk_EQ><relational_expression>
 *                       | <tk_NEQ><relational_expression>
 *                       }
 **************************************************/
void equality_expression(void)
{
	relational_expression();
	while ((cur_token == tk_EQ) || (cur_token == tk_NEQ)) {
		getToken();
		relational_expression();
	}
}


/**************************************************
 * <relational_expression>::=<additive_expression>
 *                        {
 *                           <tk_LT><additive_expression>
 *                         | <tk_GT><additive_expression>
 *                         | <tk_LEQ><additive_expression>
 *                         | <tk_GEQ><additive_expression>
 *                        }
 **************************************************/
void relational_expression(void)
{
	additive_expression();
	while ((cur_token == tk_LT) || (cur_token == tk_LEQ) || (cur_token == tk_GT) || (cur_token == tk_GEQ)) {
		getToken();
		additive_expression();
	}
}


/**************************************************
 * <additive_expression>::=<multiplicative_expression>
 *                      {
 *                        <tk_PLUS><multiplicative_expression>
 *                      | <tk_MINUS><multiplicative_expression>
 *                      }
 **************************************************/
void additive_expression(void)
{
	multiplicative_expression();
	while ((cur_token == tk_PLUS) || (cur_token == tk_MINUS)) {
		getToken();
		multiplicative_expression();
	}
}


/**************************************************
 * <multiplicative_expression>::=<unary_expression>
 *                             {
 *                               <tk_STAR><unary_expression>
 *                             | <tk_DIVIDE><unary_expression>
 *                             | <tk_MOD><unary_expression>
 *                             }
 **************************************************/
void multiplicative_expression(void)
{
	unary_expression();
	while ((cur_token == tk_STAR) || (cur_token == tk_DIVIDE) || (cur_token == tk_MOD)) {
		getToken();
		unary_expression();
	}
}


/**************************************************
 * <unary_expression>::=<postfix_expression>
 *                    | <tk_AND><unary_expression>
 *                    | <tk_STAR><unary_expression>
 *                    | <tk_PLUS><unary_expression>
 *                    | <tk_MINUS><unary_expression>
 *                    | <sizeof_expression>
 **************************************************/
void unary_expression(void)
{
	switch (cur_token) {
	case tk_AND:
		getToken();
		unary_expression();
		break;
	case tk_STAR:
		getToken();
		unary_expression();
		break;
	case tk_PLUS:
		getToken();
		unary_expression();
		break;
	case tk_MINUS:
		getToken();
		unary_expression();
		break;
	case kw_SIZEOF:
		sizeof_expression();
		break;
	default:
		postfix_expression();
		break;
	}
}


/**************************************************
 * <sizeof_expression>::=<kw_SIZEOF><tk_openPA><type_specifier><tk_closePA>
 **************************************************/
void sizeof_expression(void)
{
	uint32_t align, size;
	Type type;

	getToken();
	skip(tk_openPA);
	type_specifier(&type);
	skip(tk_closePA);

	size = type_size(&type, &align);
	if (size < 0) {
		error("sizeof calcuating failed!");
	}
}


/**************************************************
 * <postfix_expression>::=<primary_expression>
 *                     {
 *                        <tk_openBR><expression><tk_closeBR>
 *                      | <tk_openPA><tk_closePA>
 *                      | <tk_openPA><argument_expression_list><tk_closePA>
 *                      | <tk_DOT><IDENTIFIER>
 *                      | <tk_POINTTO><IDENTIFIER>
 *                     }
 **************************************************/
void postfix_expression(void)
{
	primary_expression();
	while (1) {
		if ((cur_token == tk_DOT) || (cur_token == tk_POINTTO)) {
			getToken();
			cur_token |= JC_MEMBER;/*FIXME:maybe*/
			getToken();
		} else if (cur_token == tk_openBR) {
			getToken();
			expression();
			skip(tk_closeBR);
		} else if (cur_token == tk_openPA) {
			argument_expression_list();
		} else {
			break;
		}
	}
}


/**************************************************
 * <primary_expression>::=<IDENTIFIER>
 *                      | <tk_cINT>
 *                      | <tk_cSTR>
 *                      | <tk_cCHAR>
 *                      | <tk_openPA><expression><tk_closePA>
 **************************************************/
void primary_expression(void)
{
	uint32_t T_type;
	Type type;
	Symbol *s;

	switch (cur_token) {
	case tk_cINT:
	case tk_cCHAR:
		getToken();
		break;
	case tk_cSTR:
		T_type = T_CHAR;
		type.data_type = T_type;
		mk_pointer(&type);
		type.data_type |= T_ARRAY;
		var_sym_put(&type, JC_GLOBAL, NOT_SPECIFIED, NOT_SPECIFIED);
		initializer(&type);
		break;
	case tk_openPA:
		getToken();
		expression();
		skip(tk_closePA);
		break;
	default:
		T_type = cur_token;
		getToken();
		if (cur_token < tk_IDENT) {
			expect("Identifier or constant value(char/string/number)");
		}
		s = sym_search(T_type);
		if (!s) {
			if (cur_token != tk_openPA) {
				error("'%s' is undeclared!", get_tkSTR(T_type));
			}
			s = func_sym_push(T_type, &default_func_type); /*Allowing function can be invoked without declaration*/
			s->storage_type = JC_GLOBAL | JC_SYM;
		}
		break;
	}
}


/**************************************************
 * <argument_expression_list>::=<assignment_expression>{<tk_COMMA><assignment_expression>}
 **************************************************/
void argument_expression_list(void)
{
	getToken();
	if (cur_token != tk_closePA) {
		while (1) {
			assignment_expression();
			if (cur_token == tk_closePA) {
				break;
			}
			skip(tk_COMMA);
		}
	}
	skip(tk_closePA);
}













