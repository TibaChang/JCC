#ifndef __GLOBAL_VAR_H
#define __GLOBAL_VAR_H

#include <stdint.h>
#include <stdio.h>
#include "token.h"
#include "tkWord_Hash.h"
#include "dynARR.h"
#include "dynSTR.h"

/*Lexcial analysis*/
extern tkWord *tk_hashTable[MAX_KEY];
extern dynARR tkTable;
/*In get_tkSTR(),if the target token is constant string/character/number, we get string from dynSTR sourceSTR */
extern dynSTR sourceSTR;
/* For identifying (new) token purpose. */
extern dynSTR cur_tkSTR;
extern int tkValue;
extern uint32_t cur_token;
extern uint32_t compiler_stage;
extern uint32_t cur_line_num;
/*Indicating where are we in the JCC source file.*/
extern char cur_CHAR;
/*The target JCC source file*/
extern FILE *cur_File;
extern char *cur_filename;
/**************************************************************/

/*Syntax analysis*/

typedef enum{
    SNTX_NUL,   /* No indent behavior */
    SNTX_SP,    /* space */
    SNTX_NL_ID, /* New Line and InDent,for every declaration,function definition and end of statement */
    SNTX_DELAY  /* Confirm the format until the next word */
}SyntaxState;

typedef enum{
    SC_GLOBAL,
    SC_LOCAL,
    /*FIXME:
     * There will be more definition here.
     * */
}StorageClass;

extern uint32_t syntax_state;
extern uint32_t syntax_indent_level;
/**************************************************************/

#endif
