#ifndef __dynSTR_H_
#define __dynSTR_H_
#include <stdint.h>

/*dynamic string definition*/
typedef struct {
	uint32_t count;
	char *data;
	uint32_t capacity;
} dynSTR;

void dynSTR_init(dynSTR *pSTR, uint32_t init_size);
void dynSTR_free(dynSTR *pSTR);
void dynSTR_reInit(dynSTR *pSTR);
void dynSTR_charConcat(dynSTR *pSTR, int ch);

#endif
