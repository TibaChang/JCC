#include <stdlib.h>
#include <stdio.h>
#include "global_var.h"
#include "token.h"
#include "tkWord_Hash.h"
#include "exception.h"
#include "lex.h"

void handle_exception(int level, char *fmt, va_list ap)
{
	char buffer[1024];
	vsprintf(buffer, fmt, ap);
	if (compiler_stage == LEVEL_WARNING) {
		printf("In the file:%s, line number:%d ,Compiler WARNING:%s\n", cur_filename, cur_line_num, buffer);
	} else {
		printf("In the file:%s, line number:%d ,Compiler ERROR:%s\n", cur_filename, cur_line_num, buffer);
		exit(EXIT_FAILURE);
	}
}

void warning(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	handle_exception(LEVEL_WARNING, fmt, ap);
	va_end(ap);
}

void error(char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	handle_exception(LEVEL_ERROR, fmt, ap);
	va_end(ap);
}

void expect(char *msg)
{
	error("COMPILER EXPECT:%s", msg);
}

void skip(uint32_t tk)
{
	if (cur_token != tk) {
		expect(get_tkstr(tk));
	}
	getToken();
}

char *get_tkstr(uint32_t tk_code)
{
	if (tk_code > tkTable.count) {
		return NULL;
	} else if ((tk_code >= tk_cINT) && (tk_code <= tk_cSTR)) {
		return sourceSTR.data;
	}

	return (((tkWord*)tkTable.data[tk_code])->str);
}
