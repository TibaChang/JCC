#ifndef __GLOBAL_VAR_H
#define __GLOBAL_VAR_H

#include <stdint.h>
#include "token.h"
#include "tkWord_Hash.h"
#include "dynARR.h"
#include "dynSTR.h"

extern tkWord *tk_hashTable[MAX_KEY];
extern dynARR tkTable;
extern dynSTR sourceSTR;
extern uint32_t current_token;
extern uint32_t compiler_stage;
extern uint32_t cur_line_num;
extern char *cur_filename;



#endif
