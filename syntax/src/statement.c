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
#include "declaration.h"
#include "global_var.h"
#include "token.h"
#include "exception.h"
#include "lex.h"
#include "statement.h"
#include "expression.h"
#include "reg.h"

/********************************************
 * <statement>::=<compound_statement>
 *             | <if_statement>
 *             | <return_statement>
 *             | <break_statement>
 *             | <continue_statement>
 *             | <for_statement>
 *             | <expression_statement>
 ********************************************/
void statement(uint32_t *break_sym, uint32_t *continue_sym)
{
	switch (cur_token) {
	case tk_BEGIN:
		compound_statement(break_sym, continue_sym);
		break;
	case kw_IF:
		if_statement(break_sym, continue_sym);
		break;
	case kw_RETURN:
		return_statement();
		break;
	case kw_BREAK:
		break_statement();
		break;
	case kw_CONTINUE:
		continue_statement();
		break;
	case kw_FOR:
		for_statement(break_sym, continue_sym);
		break;
	default:
		expression_statement();
		break;
	}
}



/********************************************
 * <compound_statement>::=<tk_BEGIN>{<declaration>}{<statement>}<tk_END>
 ********************************************/
void compound_statement(uint32_t *break_sym, uint32_t *continue_sym)
{
	Symbol *s;
	s = (Symbol*)stack_get_top(&local_sym_stack);

	/*JCC only support declarae local variable before any statement*/
	getToken();
	while (is_type_specifier(cur_token)) {
		external_declaration(JC_LOCAL);
	}


	while (cur_token != tk_END) {
		statement(break_sym, continue_sym);
	}
	sym_pop(&local_sym_stack, s);
	getToken();
}


/********************************************
 * To knopw whether it is type specifier
 ********************************************/
uint32_t is_type_specifier(uint32_t tk_code)
{
	switch (tk_code) {
	case kw_CHAR:
	case kw_INT:
	case kw_VOID:
	case kw_STRUCT:
		return 1;
	default:
		break;
	}
	return 0;
}


/********************************************
 * <expression_statement>::=<tk_SEMICOLON>
 ********************************************/
void expression_statement(void)
{
	if (cur_token != tk_SEMICOLON) {
		expression();
	}
	skip(tk_SEMICOLON);
}



/********************************************
 * <if_statement>::=<kw_IF><tk_openPA><expression><tk_closePA><statement>[<kw_ELSE><statement>]
 ********************************************/
void if_statement(uint32_t *break_sym, uint32_t *continue_sym)
{
	getToken();
	skip(tk_openPA);
	expression();
	skip(tk_closePA);
	statement(break_sym, continue_sym);
	if (cur_token == kw_ELSE) {
		getToken();
		statement(break_sym, continue_sym);
	}
}


/********************************************
 * <for_statement>::=
 *               <kw_FOR><tk_openPA><expression_statement><expression_statement><expression><tk_closePA><statement>
 *******************************************/
void for_statement(uint32_t *break_sym, uint32_t *continue_sym)
{
	getToken();
	skip(tk_openPA);
	if (cur_token != tk_SEMICOLON) {
		/*The reason why we do not use expression_statement() is due to expression_statement() may indent the code!*/
		expression();
	}
	skip(tk_SEMICOLON);

	if (cur_token != tk_SEMICOLON) {
		/*The reason why we do not use expression_statement() is due to expression_statement() may indent the code!*/
		expression();
	}
	skip(tk_SEMICOLON);

	if (cur_token != tk_closePA) {
		expression();
	}

	skip(tk_closePA);
	statement(break_sym, continue_sym);
}


/*********************************************
 * <continue_statement>::=<kw_CONTINUE><tk_SEMICOLON>
 *********************************************/
void continue_statement(void)
{
	getToken();
	skip(tk_SEMICOLON);
}


/*********************************************
 * <break_statement>::=<kw_BREAK><tk_SEMICOLON>
 *********************************************/
void break_statement(void)
{
	getToken();
	skip(tk_SEMICOLON);
}


/*********************************************
 * <return_statement>::=<kw_RETURN><tk_SEMICOLON>
 *                    | <kw_RETURN><expression><tk_SEMICOLON>
 *********************************************/
void return_statement(void)
{
	getToken();

	if (cur_token != tk_SEMICOLON) {
		expression();
	}
	skip(tk_SEMICOLON);
}

















