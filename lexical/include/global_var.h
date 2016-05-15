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
extern dynSTR sourceSTR;
extern dynSTR cur_tkSTR;
extern int tkValue;
extern uint32_t cur_token;
extern uint32_t compiler_stage;
extern uint32_t cur_line_num;
extern char *cur_filename;
extern char cur_CHAR;
extern FILE *cur_File;



#endif
