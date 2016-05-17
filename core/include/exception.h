#ifndef __EXCEPTION_H
#define __EXCEPTION_H
#include <stdint.h>
#include <stdarg.h>
#include "dynARR.h"
#include "token.h"

typedef enum {
	LEVEL_WARNING,
	LEVEL_ERROR,
} ErrorLevel;

void warning(char *fmt, ...);
void error(char *fmt, ...);
void expect(char *msg);
void skip(TOKEN tk);

#endif
