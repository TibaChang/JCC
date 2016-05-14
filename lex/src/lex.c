#include <string.h>
#include <stdio.h>
#include "lex.h"
#include "global_var.h"
#include "token.h"
#include "tkWord_Hash.h"
#include "exception.h"

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

void getCHAR(void)
{
	cur_CHAR = getc(cur_File);
}

void getToken(void)
{
	/*FIXME
	 *preprocess();
	 */
	switch (cur_CHAR) {
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	case '_': {
			tkWord *tkp;
			/*FIXME
			 *parse_identifier();
			 */
			tkp = tkW_insert(cur_tkSTR.data);
			cur_token = tkp->tkCode;
			break;
		}

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9': {
			/*FIXME
			 *parse_num();
			 */
			cur_token = tk_cINT;
			break;
		}
	case '+': {
			getCHAR();
			cur_token = tk_PLUS;
			break;
		}
	case '-': {
			getCHAR();
			if (cur_CHAR == '>') {
				cur_token = tk_POINTTO;
				getCHAR();
			} else {
				cur_token = tk_MINUS;
			}
			break;
		}
	case '/': {
			cur_token = tk_DIVIDE;
			getCHAR();
			break;
		}
	case '%': {
			cur_token = tk_MOD;
			getCHAR();
			break;
		}
	case '=': {
			getCHAR();
			if (cur_CHAR == '=') {
				cur_token = tk_EQ;
				getCHAR();
			} else {
				cur_token = tk_ASSIGN;
			}
			break;
		}
	case '!': {
			getCHAR();
			if (cur_CHAR == '=') {
				cur_token = tk_NEQ;
			} else {
				error("The COMPILER DOR NOT SUPPORT \"!\" operand. \n");
			}
			break;
		}
	case '<': {
			getCHAR();
			if (cur_CHAR == '=') {
				cur_token = tk_LEQ;
				getCHAR();
			} else {
				cur_token = tk_LT;
			}
			break;
		}
	case '>': {
			getCHAR();
			if (cur_CHAR == '=') {
				cur_token = tk_GEQ;
				getCHAR();
			} else {
				cur_token = tk_GT;
			}
			break;
		}
	case '.': {
			getCHAR();
			if (cur_CHAR == '.') {
				getCHAR();
				if (cur_CHAR == '.') {
					cur_token = tk_ELLIPSIS;
				} else {
					error(" \"...\"ellipse spelling ERROR! \n");
				}
				getCHAR();
			} else {
				cur_token = tk_DOT;
			}
			break;
		}
	case '&': {
			cur_token = tk_AND;
			getCHAR();
			break;
		}
	case ';': {
			cur_token = tk_SEMICOLON;
			getCHAR();
			break;
		}
	case ']': {
			cur_token = tk_closeBR;
			getCHAR();
			break;
		}
	case '}': {
			cur_token = tk_END;
			getCHAR();
			break;
		}
	case ')': {
			cur_token = tk_closePA;
			getCHAR();
			break;
		}
	case '[': {
			cur_token = tk_openBR;
			getCHAR();
			break;
		}
	case '{': {
			cur_token = tk_BEGIN;
			getCHAR();
			break;
		}
	case '(': {
			cur_token = tk_openPA;
			getCHAR();
			break;
		}
	case ',': {
			cur_token = tk_COMMA;
			getCHAR();
			break;
		}
	case '*': {
			cur_token = tk_STAR;
			getCHAR();
			break;
		}
	case '\'': {
			/*FIXME
			 *parse_string(cur_CHAR);
			 */
			cur_token = tk_cCHAR;
			tkValue = *(char*)cur_tkSTR.data;
			break;
		}
	case '\"': {
			/*FIXME
			 *parse_string(cur_CHAR);
			 */
			cur_token = tk_cSTR;
			break;
		}
	case EOF: {
			cur_token = tk_EOF;
			break;
		}
	default: {
			error("CANNOT identify this character:%s \n", cur_CHAR);
			getCHAR();
			break;
		}

	}/*END of switch*/
}

