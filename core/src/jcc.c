#include <stdio.h>
#include "dynSTR.h"
#include "dynARR.h"

int main()
{
	printf("LEX\n");
	dynARR tmp;
	dynARR_init(&tmp, 20);
	dynARR_free(&tmp);
}
