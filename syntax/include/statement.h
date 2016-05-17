#ifndef __STATEMENT_H_
#define __STATEMENT_H_
#include "token.h"

void statement(void);
void compound_statement(void);
uint32_t is_type_specifier(TOKEN tk_code);
void expression_statement(void);
void if_statement(void);
void for_statement(void);
void continue_statement(void);
void break_statement(void);
void return_statement(void);

#endif
