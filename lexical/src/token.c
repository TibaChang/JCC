#include "token.h"
#include "global_var.h"
#include "tkWord_Hash.h"

char *get_tkSTR(TOKEN tk_code)
{
	if (tk_code > tkTable.count) {
		return NULL;
	} else if ((tk_code >= tk_cINT) && (tk_code <= tk_cSTR)) {
		return sourceSTR.data;
	}

	return (((tkWord*)tkTable.data[tk_code])->str);
}

