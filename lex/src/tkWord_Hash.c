#include <string.h>
#include <stdlib.h>
#include "global_var.h"
#include "tkWord_Hash.h"
#include "dynARR.h"
#include "debug.h"

/*ref:https://en.wikipedia.org/wiki/MurmurHash*/
uint32_t hash_func(const char *key, uint32_t len)
{
	static const uint32_t c1 = 0xcc9e2d51;
	static const uint32_t c2 = 0x1b873593;
	static const uint32_t r1 = 15;
	static const uint32_t r2 = 13;
	static const uint32_t m = 5;
	static const uint32_t n = 0xe6546b64;

	uint32_t hash = HASH_SEED;

	const int nblocks = len / 4;
	const uint32_t *blocks = (const uint32_t *) key;
	int i;
	uint32_t k;
	for (i = 0; i < nblocks; i++) {
		k = blocks[i];
		k *= c1;
		k = ROT32(k, r1);
		k *= c2;

		hash ^= k;
		hash = ROT32(hash, r2) * m + n;
	}

	const uint8_t *tail = (const uint8_t *)(key + nblocks * 4);
	uint32_t k1 = 0;

	switch (len & 3) {
	case 3:
		k1 ^= tail[2] << 16;
	case 2:
		k1 ^= tail[1] << 8;
	case 1:
		k1 ^= tail[0];

		k1 *= c1;
		k1 = ROT32(k1, r1);
		k1 *= c2;
		hash ^= k1;
	}

	hash ^= len;
	hash ^= (hash >> 16);
	hash *= 0x85ebca6b;
	hash ^= (hash >> 13);
	hash *= 0xc2b2ae35;
	hash ^= (hash >> 16);

	return (hash % MAX_KEY);
}


tkWord *tkW_direct_insert(tkWord *tkp)
{
	uint32_t key_no;
	/*FIXME
	 *sym_struct
	 *sym_identifier
	 */
	dynARR_add(&tkTable, tkp);
	key_no = hash_func(tkp->str, tkp->str_len);

	/*save the previous tkWord to it for hash conflict.*/
	tkp->next = tk_hashTable[key_no];

	tk_hashTable[key_no] = tkp;
	return tkp;
}


tkWord *tkW_search(char *p, uint32_t key_no)
{
	tkWord *tkp = NULL;
	for (tkWord *tkp_1 = tk_hashTable[key_no]; tkp_1 != NULL ; tkp_1 = tkp_1->next) {
		if (!strncmp(p, tkp_1->str, tkp_1->str_len)) {
			current_token = tkp_1->tkCode;
			tkp = tkp_1;
			DBG_printf("In tkW_search() : find token!\n");
			break;
		}
	}
	return tkp;
}


tkWord *tkW_insert(char *p)
{
	tkWord *tkp;
	uint32_t key_no;
	uint32_t length;

	key_no = hash_func(p, strlen(p));
	tkp = tkW_search(p, key_no);

	if (tkp == NULL) {
		length = strlen(p);
		tkp = (tkWord*)mallocZ(sizeof(tkWord) + length + 1);
		tkp->next = tk_hashTable[key_no];
		tk_hashTable[key_no] = tkp;

		dynARR_add(&tkTable, tkp);
		tkp->tkCode = tkTable.count - 1;

		char *s = (char*)tkp + sizeof(tkWord);
		tkp->str = (char *)s;
		for (char *end = p + length; p < end;) {
			*s++ = *p++;
		}
		*s = (char)'\0';
	}
	return tkp;
}


void *mallocZ(uint32_t size)
{
	void *ptr = malloc(size);
	if ((!ptr) || size) {
		perror("mallocZ failed!\n");
	}
	memset(ptr, 0, size);
	return ptr;
}









