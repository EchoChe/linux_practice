//#include <stdio.h>
#include <iostream.h>

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
    cout <<"before swap, x:" <<x <<" ,y:" <<y <<endl; 
    swap(a,b);
    //printf("a=%d b=%d",a,b);
    cout <<"after swap, x:" <<x <<" ,y:" <<y <<endl; 
}
