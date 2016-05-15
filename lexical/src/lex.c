#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lex.h"
#include "global_var.h"
#include "token.h"
#include "tkWord_Hash.h"
#include "exception.h"
#include "dynSTR.h"

static void preProcess(void);
static void parseComment(void);
static void skip_white_space(void);
static uint32_t is_NOdigit(char c); 
static uint32_t is_digit(char c);
static void parse_identifier(void);
static void parse_num(void);
static void parse_string(char sep);

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
	preProcess();

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
			parse_identifier();

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
			parse_num();
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
			parse_string(cur_CHAR);
			cur_token = tk_cCHAR;
			tkValue = *(char*)cur_tkSTR.data;
			break;
		}
	case '\"': {
			parse_string(cur_CHAR);
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

static void preProcess(void)
{
	while (1) {
		if ((cur_CHAR == ' ') || (cur_CHAR == '\t') || (cur_CHAR == '\r') || (cur_CHAR == '\n')) {
			skip_white_space();
		} else if (cur_CHAR == '/') {
			/* look ahead one character */
			getCHAR();
			if (cur_CHAR == '*') {
				parseComment();
			} else {
				ungetc(cur_CHAR, cur_File); /*put it back*/
				cur_CHAR = '/';
				break;
			}
		} else {
			break;
		}
	}
}


void parseComment(void)
{
	getCHAR();
	while (1) {
		while (1) {
			if ((cur_CHAR == '\n') || (cur_CHAR == '*') || (cur_CHAR == EOF)) {
				break;
			} else {
				getCHAR();
			}
		}

		if (cur_CHAR == '\n') {
			cur_line_num++;
			getCHAR();
		} else if (cur_CHAR == '*') {
			getCHAR();
			if (cur_CHAR == '/') {
				getCHAR();
				return;
			}
		} else {
			error("CANNOT find the end of comment until the end of file! \n");
			return;
		}
	}
}

void skip_white_space(void)
{
	while ((cur_CHAR == ' ') || (cur_CHAR == '\t') || (cur_CHAR == '\r') || (cur_CHAR == '\n')) {
		/*Windows*/
		if (cur_CHAR == '\r') {
			getCHAR();
			if (cur_CHAR != '\n') {
				return;
			}
			cur_line_num++;
		}

		/*Unix,excluding MAC OS*/
		if (cur_CHAR == '\n') {

			cur_line_num++;
		}

		printf("%c", cur_CHAR);
		getCHAR();
	}
}

static uint32_t is_NOdigit(char c)
{
	return (((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || (c == '_'));
}

static uint32_t is_digit(char c)
{
	return ((c >= '0') && (c <= '9'));
}

static void parse_identifier(void)
{
	dynSTR_reInit(&cur_tkSTR);
	dynSTR_charConcat(&cur_tkSTR, cur_CHAR);
	getCHAR();

	while (is_NOdigit(cur_CHAR) || is_digit(cur_CHAR)) {
		dynSTR_charConcat(&cur_tkSTR, cur_CHAR);
		getCHAR();
	}
	dynSTR_charConcat(&cur_tkSTR, '\0');
}

static void parse_num(void)
{
	dynSTR_reInit(&cur_tkSTR);
	dynSTR_reInit(&sourceSTR);

	do {
		dynSTR_charConcat(&cur_tkSTR, cur_CHAR);
		dynSTR_charConcat(&sourceSTR, cur_CHAR);
		getCHAR();
	} while (is_digit(cur_CHAR));

	if (cur_CHAR == '.') {
		do {
			dynSTR_charConcat(&cur_tkSTR, cur_CHAR);
			dynSTR_charConcat(&sourceSTR, cur_CHAR);
			getCHAR();
		} while (is_digit(cur_CHAR));
	}

	dynSTR_charConcat(&cur_tkSTR, '\0');
	dynSTR_charConcat(&sourceSTR, '\0');
	tkValue = atoi(cur_tkSTR.data);
}


/*
 * sep:
 * '\'' or '\"'
 */
static void parse_string(char sep)
{
	char c;
	dynSTR_reInit(&cur_tkSTR);
	dynSTR_reInit(&sourceSTR);
	dynSTR_charConcat(&sourceSTR, sep);
	getCHAR();

	while (1) {
		/* Ex: "" or '' */
		if (cur_CHAR == sep) {
			break;
		} else if (cur_CHAR == '\\') {
			/*escapes*/
			dynSTR_charConcat(&sourceSTR, cur_CHAR);
			getCHAR();
			switch (cur_CHAR) {
			case '0':
				c = '\0';
				break;
			case 'a':
				c = '\a';
				break;
			case 'b':
				c = '\b';
				break;
			case 't':
				c = '\t';
				break;
			case 'n':
				c = '\n';
				break;
			case 'v':
				c = '\v';
				break;
			case 'f':
				c = '\f';
				break;
			case 'r':
				c = '\r';
				break;
			case '\"':
				c = '\"';
				break;
			case '\'':
				c = '\'';
				break;
			case '\\':
				c = '\\';
				break;
			default:
				c = cur_CHAR;
				if ((c >= '!') && (c <= '~')) {
					/*In the possible escapes range,it matches nothing!*/
					warning("FOUND: NOT escapes-> \' \\%c \' !\n", c);
				} else {
					/*Impossible range for escapes!*/
					warning("FOUND: NOT escapes-> \' \\0x%x \' \n", c);
				}
				break;
			}
			dynSTR_charConcat(&cur_tkSTR, c);
			dynSTR_charConcat(&sourceSTR, cur_CHAR);
			getCHAR();
		} else {
			dynSTR_charConcat(&cur_tkSTR, cur_CHAR);
			dynSTR_charConcat(&sourceSTR, cur_CHAR);
			getCHAR();
		}
	}

	dynSTR_charConcat(&cur_tkSTR, '\0');

	dynSTR_charConcat(&sourceSTR, sep);
	dynSTR_charConcat(&sourceSTR, '\0');

	getCHAR();
}






















