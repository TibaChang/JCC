#include <stdint.h>
#include "syntax_indent.h"
#include "global_var.h"
#include "jcc.h"

static void print_tab(uint32_t tab_num)
{
	for (uint32_t i = 0; i < tab_num; i++) {
		printf("\t");
	}
}


void syntax_indent(void)
{
	switch (syntax_state) {
	case SNTX_NUL:
		color_token(LEX_NORMAL);
		break;
	case SNTX_SP:
		printf(" ");
		color_token(LEX_NORMAL);
		break;
	case SNTX_NL_ID:
		if (cur_token == tk_END) {
			syntax_indent_level--;
		}
		printf("\n");
		print_tab(syntax_indent_level);

		color_token(LEX_NORMAL);
		break;
	case SNTX_DELAY:
		break;
	}
	syntax_state = SNTX_NUL;
}

