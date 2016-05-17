#include <stdint.h>
#include "declaration.h"
#include "global_var.h"
#include "token.h"
#include "exception.h"
#include "lex.h"
#include "syntax_indent.h"
#include "statement.h"
#include "expression.h"

/********************************************
 * <statement>::=<compound_statement>
 *             | <if_statement>
 *             | <return_statement>
 *             | <break_statement>
 *             | <continue_statement>
 *             | <for_statement>
 *             | <expression_statement>
 ********************************************/
void statement(void)/*FIXME:maybe*/
{
	switch (cur_token) {
	case tk_BEGIN:
		compound_statement();
		break;
	case kw_IF:
		if_statement();
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
		for_statement();
		break;
	default:
		expression_statement();
		break;
	}
}



/********************************************
 * <compound_statement>::=<tk_BEGIN>{<declaration>}{<statement>}<tk_END>
 ********************************************/
void compound_statement(void)
{
	syntax_state = SNTX_NL_ID;
	syntax_indent_level++;

	getToken();
	while (is_type_specifier(cur_token)) {
		external_declaration(JC_LOCAL);
	}

	while (cur_token != tk_END) {
		statement();
	}
}


/********************************************
 * To knopw whether it is type specifier
 ********************************************/
uint32_t is_type_specifier(TOKEN tk_code)
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
	syntax_state = SNTX_NL_ID;
	skip(tk_SEMICOLON);
}



/********************************************
 * <if_statement>::=<kw_IF><tk_openPA><expression><tk_closePA><statement>[<kw_ELSE><statement>]
 ********************************************/
void if_statement(void)
{
	syntax_state = SNTX_SP;
	getToken();
	skip(tk_openPA);
	expression();
	syntax_state = SNTX_NL_ID;
	skip(tk_closePA);
	statement();
	if (cur_token == kw_ELSE) {
		syntax_state = SNTX_NL_ID;
		getToken();
		statement();
	}
}


/********************************************
 * <for_statement>::=
 *               <kw_FOR><tk_openPA><expression_statement><expression_statement><expression><tk_closePA><statement>
 *******************************************/
void for_statement(void)
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

	syntax_state = SNTX_NL_ID;
	skip(tk_closePA);
	statement();
}


/*********************************************
 * <continue_statement>::=<kw_CONTINUE><tk_SEMICOLON>
 *********************************************/
void continue_statement(void)
{
	getToken();
	syntax_state = SNTX_NL_ID;
	skip(tk_SEMICOLON);
}


/*********************************************
 * <break_statement>::=<kw_BREAK><tk_SEMICOLON>
 *********************************************/
void break_statement(void)
{
	getToken();
	syntax_state = SNTX_NL_ID;
	skip(tk_SEMICOLON);
}


/*********************************************
 * <return_statement>::=<kw_RETURN><tk_SEMICOLON>
 *                    | <kw_RETURN><expression><tk_SEMICOLON>
 *********************************************/
void return_statement(void)
{
	syntax_state = SNTX_DELAY;
	getToken();
	if (cur_token == tk_SEMICOLON) {
		syntax_state = SNTX_NUL;
	} else {
		syntax_state = SNTX_SP;
	}
	syntax_indent();

	if (cur_token != tk_SEMICOLON) {
		expression();
	}
	syntax_state = SNTX_NL_ID;
	skip(tk_SEMICOLON);
}

















