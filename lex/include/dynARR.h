#ifndef __dynARR_H_
#define __dynARR_H_
#include <stdint.h>

/*dynamic string definition*/
typedef struct {
	uint32_t count;
	void **data;
	uint32_t capacity;
} dynARR;

void dynARR_init(dynARR *pARR,uint32_t init_size);
void dynARR_free(dynARR *pARR);
int dynARR_search(dynARR *pARR,int key);
void dynARR_realloc(dynARR *pARR,uint32_t new_size);
void dynARR_add(dynARR *pARR,void *data);

#endif
