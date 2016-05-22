/*
 * Copyright (c) 2016, Chang Jia-Rung, All Rights Reserved
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
	error(" JCC EXPECTED:%s", msg);
}

void skip(TOKEN tk)
{
	if (cur_token != tk) {
		expect(get_tkSTR(tk));
	}
	getToken();
}



