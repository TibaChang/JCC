
struct PP {
	int a;
}

/*TEST 
 *
 * comment 1*/

char sss = 'c';

void main()
{
	int testArr[50];
	int X;
	struct PP sample;
	PP.a = 1000;

	for (X = 0; X < 100; X++) {
		if (X == 50) {
			break;
		} else {
			PP.a = 500;
		}
	}
	printf("test \n");
}


