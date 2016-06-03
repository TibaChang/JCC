
char gc = 'c';

void main()
{
    int cc = 'c';
    char *test = "end\n";
    int a = 5;
    int c = 1000;
    if(100 != 5)
    {
        printf("correct\n");
        if( 100 != 5)
        {
            printf("nested if!\n");
        }
        if( gc == cc)
        {
            printf("nested if!\n");
        }
    }
    printf("%s",test);
}


