


void main()
{
    int term = 44;
	int first = 0, second = 1, next, i;
 
   	printf("First %d terms of Fibonacci series are :\n",term);
 
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


