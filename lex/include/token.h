#ifndef __TOKEN_H_
#define __TOKEN_H_
#include <stdint.h>

typedef enum {
	/*OPERAND and SEPARATION SYMBOL*/
	tk_PLUS,     // +
	tk_MINUS,    // -
	tk_STAR,     // *
	tk_DIVIDE,   // /
	tk_MOD,      // %
	tk_EQ,       // ==
	tk_NEQ,      // !=
	tk_LT,       // <
	tk_LEQ,      // <=
	tk_GT,       // >
	tk_GEQ,      // >=
	tk_ASSIGN,   // =
	tk_POINTTO,  // ->
	tk_DOT,      // .
	tk_AND,      // &
	tk_openPA,   // (
	tk_closePA,  // )
	tk_openBR,   // [
	tk_closeBR,  // ]
	tk_BEGIN,    // {
	tk_END,      // }
	tk_SEMICOLON,// ;
	tk_COMMA,    // ,
	tk_ELLIPSIS, // ...
	tk_EOF,      // END OF FILE

	/*CONSTANTS*/
	tk_cINT,     // const. integer
	tk_cCHAR,    // const. char
	tk_cSTR,     // const. STRING

	/*KEY WORDS*/
	kw_CHAR,     // char
	kw_INT,      // int
	kw_VOID,     // void
	kw_STRUCT,   // struct

	kw_IF,       // if
	kw_ELSE,     // else
	kw_FOR,      // for
	kw_CONTINUE, // continue
	kw_BREAK,    // break
	kw_RETURN,   // return
	kw_SIZEOF,   // sizeof

	/*IDENTIFIERS*/
	tk_IDENT
} TOKEN;

char *get_tkSTR(uint32_t tk_code);

#endif
