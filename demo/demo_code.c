

char *global_str = "global_var \n";

int b = 1000;

void main()
{
    int a = 5;
    int c = 1000;
    char *local_str = "local_str\n";
    printf("test str%d \n %d\n %s \n",b,a,global_str);
    printf("test str%d \n %d\n %s \n",b,a,global_str);

    a = a+c;

    printf("%d\n",a);

    c= c*c*c;
    printf("%d\n",c);
}


