#include "global_var.h"
#include "token.h"

/*Lexical analysis*/
tkWord *tk_hashTable[MAX_KEY];
dynARR tkTable;
dynSTR sourceSTR;
dynSTR cur_tkSTR;
int tkValue;
TOKEN cur_token;
uint32_t compiler_stage;
uint32_t cur_line_num;
char *cur_filename;
char cur_CHAR;
FILE *cur_File;


/*Syntax analysis*/
uint32_t syntax_state;
uint32_t syntax_indent_level;


