#include <stdio.h>

swap(int &a, int &b)
{
    int c;
    c = a;
    a = b;
    b =c;
}

int main()
{
    int a=3, b =4;

    swap(a,b);
    printf("a=%d b=%d",a,b);
}
