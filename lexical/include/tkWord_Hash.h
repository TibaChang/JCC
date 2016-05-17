#ifndef __tkWord_Hash_H_
#define __tkWord_Hash_H_
#include <stdint.h>
#include "token.h"

/*For hash_func*/
#define ROT32(x, y) ((x << y) | (x >> (32 - y)))
#define HASH_SEED 1998
#define MAX_KEY 1024
uint32_t hash_func(const char *key, uint32_t len);

/* single word definition for storage */
typedef struct tkWord {
	TOKEN tkCode;       /*token encoding*/
	struct tkWord *next;   /*pointer to next token words if hash conflict happens*/
	char *str;             /*token string(how to spell)*/
	uint32_t str_len;      /*token string length*/
	/*FIXME:struct member
	 *sym_struct
	 *sym_identifier
	 */
} tkWord;

tkWord *tkW_direct_insert(tkWord *tkp);
tkWord *tkW_search(char *p, uint32_t key_no);
tkWord *tkW_insert(char *p);

#endif
