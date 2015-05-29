#include <stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int ret = 0;

	ret = scanf("%d%d%d",&a,&b,&c);
	printf("Frist counts:%d\n",ret);
	printf("a=%d,b=%d,c=%d\n",a,b,c);

	ret = scanf("%c%d%d",&a,&b,&c);	
	printf("second counts:%d\n",ret);
	printf("a=%c,b=%d,c=%d\n",a,b,c);
}
