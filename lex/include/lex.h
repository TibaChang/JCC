#ifndef __LEX_H_
#define __LEX_H_
#include <stdint.h>

void init_lex(void);
void getCHAR(void);
void getToken(void);

void preProcess(void);
void parseComment(void);
void skip_white_space(void);

uint32_t is_NOdigit(char c);
uint32_t is_digit(char c);
void parse_identifier(void);
void parse_num(void);
void parse_string(char sep);

#endif
