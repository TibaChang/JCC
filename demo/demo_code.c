
void iterative_fibobacci()
{
    int term;
	int first = 0, second = 1, next, i;
 
    printf("Please input the term number for Iterative Fibonacci Sequence:\n");
    scanf("%d",&term);
   	printf("The first %d terms of Fibonacci Sequences are :\n",term);
 
   	for ( i = 0 ; i < term ; )
   	{
    	if ( i <= 1 )
		{
        	next = i;
		}
      	else
      	{
            next = first + second;
            first = second;
            second = next;
      	}
      	printf("%d term -> %d\n",i,next);
        i =i+1;
    }
}


int gcd(int a, int b)
{
    int c;
    for(;a != 0;)
    {
        c = a;
        a = b%a;
        b = c;
    }
    return b;
}

void gcd_test()
{
    int i;
    int a,b;
    int result;
    printf("\nGCD TEST will print the gcd from your input:\n");
    printf("Please input two integer:\n");
    scanf("%d %d",&a,&b);
    result = gcd(a,b);
    printf("The result of GCD(%d,%d) is %d\n",a,b,result);
}


void main()
{
    iterative_fibobacci();
    gcd_test();
}

