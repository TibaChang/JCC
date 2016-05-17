#include <stdint.h>
#include "declaration.h"
#include "statement.h"
#include "global_var.h"
#include "token.h"
#include "exception.h"
#include "lex.h"
#include "syntax_indent.h"
#include "expression.h"

/***************************************
 *<translation_unit>::={<external_declaration>}<tk_EOF>
 ***************************************/
void translation_unit(void)
{
	while (cur_token != tk_EOF) {
		external_declaration(JC_GLOBAL);
	}
}


/***************************************
 * <external_declaration>::=<function_definition> | <declarator>
 * <function_definition>::=<type_specifier><declarator><funcbody>
 * <declarator>::=<type_specifier><tk_SEMICOLON> | <type_specifier><init_declarator_list><tk_SEMICOLON>
 * <init_declarator_list>::=<init_declarator>{<tk_COMMA><init_declarator>}
 * <init_declarator>::=<declarator>{<tk_ASSIGN><initializer>}
 *
 * Above are equivalent to:
 *
 * <external_declaration>::=<type_specifier>(
 * <tk_SEMICOLON> |
 * <declarator><funcbody> |
 * <declarator>[<tk_ASSIGN><initializer>]
 * {<tk_COMMA><declarator>[<tk_ASSIGN><initializer>]}<tk_SEMICOLON>
 * )
 ***************************************/
/*external_definition,"external" does not mean global scope
 * EX:
 * int a;                        V
 * int add(int x,int y)          V
 * {
 *     int z;                    V
 *     z = x+y;
 * }
 *
 * with the right "V",that line is "external_definition"
 * */
void external_declaration(int scope)
{
	if (!type_specifier()) {
		expect("type_specifier!\n");
	}

	if (cur_token == tk_SEMICOLON) {
		getToken();
		return;
	}

	while (1) {
		declarator();
		if (cur_token == tk_BEGIN) {
			if (scope == JC_LOCAL) {
				error("JCC does not support nested function definition!\n");
			}
			funcbody();
			break;
		} else {
			if (cur_token == tk_ASSIGN) {
				getToken();
				initializer();
			}

			if (cur_token == tk_COMMA) {
				getToken();
			} else {
				syntax_state = SNTX_NL_ID;
				skip(tk_SEMICOLON);
				break;
			}
		}
	}
}

/***************************************
 * <type_specifier>::=<kw_INT>   |
 *                    <kw_CHAR>  |
 *                    <kw_VOID>  |
 *                    <struct_specifier>
 ***************************************/
int type_specifier(void)
{
	int type_found = 0;
	switch (cur_token) {
	case kw_CHAR:
		type_found = 1;
		syntax_state = SNTX_SP;
		getToken();
		break;
	case kw_VOID:
		type_found = 1;
		syntax_state = SNTX_SP;
		getToken();
		break;
	case kw_INT:
		type_found = 1;
		syntax_state = SNTX_SP;
		getToken();
		break;
	case kw_STRUCT:
		syntax_state = SNTX_SP;
		struct_specifier();
		type_found = 1;
		break;
	default:
		break;
	}
	return type_found;
}


/***************************************
 * <struct_specifier>::=<kw_STRUCT><IDENTIFIER><tk_BEGIN><struct_declaration_list><tk_END>
 *                    | <kw_STRUCT><IDENTIFIER>
 ***************************************/
void struct_specifier(void)
{
	getToken();
	TOKEN tk = cur_token;
	syntax_state = SNTX_DELAY;
	getToken();

	if (cur_token == tk_BEGIN) {
		syntax_state = SNTX_NL_ID;/*for struct definition*/
	} else if (cur_token == tk_closePA) {
		syntax_state = SNTX_NUL; /*for sizeof(struct struct_name)*/
	} else {
		syntax_state = SNTX_SP;
	}
	syntax_indent();

	if (tk < tk_IDENT) {
		expect("struct name!\n");
	}

	if (cur_token == tk_BEGIN) {
		struct_declaration_list();
	}
}

/****************************************
 * <struct_declaration_list>::=<struct_declaration>{<struct_declaration>}
 ****************************************/
void struct_declaration_list(void)
{
	syntax_state = SNTX_NL_ID;/*struct member put in the next line*/
	syntax_indent_level++; /*struct member indent level++ */

	getToken();
	while (cur_token != tk_END) {
		struct_declaration();
	}
	skip(tk_END);

	syntax_state = SNTX_NL_ID;
}


/****************************************
 * <struct_declaration>::=<type_specifier><struct_declaration_list><tk_SEMICOLON>
 * <struct_declaration_list>::=<declarator>{<tk_COMMA><declarator>}
 *
 * Above are equivalent to:
 *
 * <struct_declaration>::=<type_specifier><declarator>{<tk_COMMA><declarator>}<tk_SEMICOLON>
 ****************************************/
void struct_declaration(void)
{
	type_specifier();
	while (1) {
		declarator();

		if (cur_token == tk_SEMICOLON) {
			break;
		}
		skip(tk_COMMA);
	}
	syntax_state = SNTX_NL_ID;
	skip(tk_SEMICOLON);
}



/****************************************
 * <declarator>::={<pointer>}<direct_declarator>
 * <pointer>::=<tk_STAR>
 *
 * Above are equivalent to :
 *
 * <declarator>::={<tk_STAR>}<direct_declarator>
 ****************************************/
void declarator(void)
{
	while (cur_token == tk_STAR) {
		getToken();
	}
	direct_declarator();
}


/****************************************
 * <direct_declarator>::=<IDENTIFIER><direct_declarator_postfix>
 ****************************************/
void direct_declarator(void)
{
	if (cur_token >= tk_IDENT) {
		getToken();
	} else {
		expect("Identifier!\n");
	}
	direct_declarator_postfix();
}



/****************************************
 * <direct_declarator_postfix>::={<tk_openBR><tk_cINT><tk_closeBR>
 *                                | <tk_openBR><tk_closeBR>
 *                                | <tk_openPA><parameter_type_list><tk_closePA>
 *                                | <tk_openPA><tk_closePA>
 * }
 ****************************************/
void direct_declarator_postfix(void)
{
	if (cur_token == tk_openPA) {
		parameter_type_list();
	} else if (cur_token == tk_openBR) {
		getToken();
		if (cur_token == tk_cINT) {
			getToken();
			/*FIXME:maybe*/
		}
		skip(tk_closeBR);
		direct_declarator_postfix();
	}
}


/****************************************
 * <parameter_type_list>::=<parameter_list> | <parameter_list><tk_COMMA><tk_ELLIPSIS>
 * <parameter_list>::<parameter_declaration>{<tk_COMMA><parameter_declaration>}
 * <parameter_declaration>::=<type_specifier>{<declarator>}
 *
 * Above are equivalent to:
 *
 * <parameter_type_list>::=<type_specifier>{<declarator>}{<tk_COMMA><type_specifier>{declarator}}{<tk_COMMA><tk_ELLIPSIS>}
 ****************************************/
void parameter_type_list(void)/*FIXME:argument*/
{
	getToken();
	while (cur_token != tk_closePA) {
		if (!type_specifier()) {
			error("Unknown type identifier!\n");
		}
		declarator();
		if (cur_token == tk_closePA) {
			break;
		}
		skip(tk_COMMA);
		if (cur_token == tk_ELLIPSIS) {
			/*FIXME:func_call*/
			getToken();
			break;
		}
	}
	syntax_state = SNTX_DELAY;
	skip(tk_closePA);

	if (cur_token == tk_BEGIN) {
		syntax_state = SNTX_NL_ID;
	} else {
		syntax_state = SNTX_NUL;
	}
	syntax_indent();
}


/****************************************
 * <funcbody>::=<compound_statement>
 ****************************************/
void funcbody(void)
{
	compound_statement();
}


/****************************************
 * <initializer>::=<assignment_expression>
 ****************************************/
void initializer(void)
{
	assignment_expression();
}














