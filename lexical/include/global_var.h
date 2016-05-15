#ifndef __GLOBAL_VAR_H
#define __GLOBAL_VAR_H

#include <stdint.h>
#include <stdio.h>
#include "token.h"
#include "tkWord_Hash.h"
#include "dynARR.h"
#include "dynSTR.h"

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



#endif
