#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "dynARR.h"

void dynARR_init(dynARR *pARR, uint32_t init_size)
{
	if (pARR != NULL) {
		pARR->data = (void**)malloc(sizeof(char) * init_size);
		pARR->capacity = init_size;
		pARR->count = 0;
	} else {
		DBG_printf("In dynARR_init(),pARR must not be NULL!\n");
	}
}

void dynARR_free(dynARR *pARR)
{
	for (void **p = pARR->data ; pARR->count > 0; p++) {
		if (*p) {
			free(*p);
			pARR->count -= 1;
		}
	}
	pARR->data = NULL;
}

int dynARR_search(dynARR *pARR, int key)
{
	int **p;
	p = (int **)pARR->data;
	for (int i = 0; i < pARR->count ; p++) {
		if (key == **p) {
			return i;
		}
	}
	return -1;
}

static void dynARR_realloc(dynARR *pARR, uint32_t new_size)
{
	if ((pARR == NULL) || (pARR->data == NULL) || (pARR->capacity == 0)) {
		DBG_printf("In dynARR_realloc,pSTR must have data or capacity!\n");
	}

	void *data;
	uint32_t capacity = 0;
	capacity = pARR->capacity;

	while (capacity < new_size) {
		capacity *= 2;
	}

	data = realloc(pARR->data, capacity);
	if (!data) {
		perror("dynARR_realloc Failed!");
	}
	pARR->data = data;
	pARR->capacity = capacity;
}

void dynARR_add(dynARR *pARR, void *data)
{
	uint32_t count = 0;
	count = pARR->count + 1;

	if (count * sizeof(void*) > pARR->capacity) {
		dynARR_realloc(pARR, count * sizeof(void*));
	}

	pARR->data[count - 1] = data;
	pARR->count = count;
}





