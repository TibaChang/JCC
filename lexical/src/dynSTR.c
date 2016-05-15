#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "dynSTR.h"

void dynSTR_init(dynSTR *pSTR, uint32_t init_size)
{
	if (pSTR != NULL) {
		pSTR->data = (char*)malloc(sizeof(char) * init_size);
		pSTR->capacity = init_size;
		pSTR->count = 0;
	} else {
		DBG_printf("In dynSTR_init(),pSTR must not be NULL!\n");
	}
}

void dynSTR_free(dynSTR *pSTR)
{
	if (pSTR != NULL) {
		if (pSTR->data) {
			free(pSTR->data);
		}
		pSTR->count = 0;
		pSTR->capacity = 0;
	} else {
		DBG_printf("In dynSTR_free(),pSTR must not be NULL!\n");
	}
}

void dynSTR_reInit(dynSTR *pSTR)
{
	dynSTR_free(pSTR);
	dynSTR_init(pSTR, 8); /*Init size = 8 bytes*/
}

static void dynSTR_realloc(dynSTR *pSTR, uint32_t new_size)
{
	if ((pSTR == NULL) || (pSTR->data == NULL) || (pSTR->capacity == 0)) {
		DBG_printf("In dynSTR_realloc,pSTR must have data or capacity!\n");
	}

	char *data;
	uint32_t capacity = 0;
	capacity = pSTR->capacity;

	while (capacity < new_size) {
		capacity *= 2;
	}

	data = realloc(pSTR->data, capacity);
	if (!data) {
		perror("dynSTR_realloc Failed!");
	}
	pSTR->data = data;
	pSTR->capacity = capacity;
}

void dynSTR_charConcat(dynSTR *pSTR, int ch)
{
	uint32_t count = 0;
	count = pSTR->count + 1;

	if (count > pSTR->capacity) {
		dynSTR_realloc(pSTR, count);
	}

	((char *)pSTR->data)[count - 1] = ch;
	pSTR->count = count;
}





