#include <stdlib.h>
#include <stdio.h>
#include "global_var.h"
#include "token.h"
#include "tkWord_Hash.h"
#include "exception.h"
#include "lex.h"

static void handle_exception(int level, char *fmt, va_list ap)
{
	char buffer[1024];
	vsprintf(buffer, fmt, ap);
	if (compiler_stage == LEVEL_WARNING) {
		printf("\nIn the file:%s, line number:%d ,Compiler WARNING:%s\n", cur_filename, cur_line_num, buffer);
	} else {
		printf("\nIn the file:%s, line number:%d ,Compiler ERROR:%s\n", cur_filename, cur_line_num, buffer);
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
	error("\nCOMPILER EXPECTED:%s\n", msg);
}

void skip(TOKEN tk)
{
	if (cur_token != tk) {
		expect(get_tkSTR(tk));
	}
	getToken();
}



