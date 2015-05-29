#include <stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int ret = 0;
	
	ret = scanf("%d%d%d",&a,&b,&c);
	fflush(stdin);
	printf("Frist count:%d\n",ret);
	printf("a=%d b=%d c=%d\n",a,b,c);
	
	ret = scanf("%d%d%d",&a,&b,&c);
	fflush(stdin);
	printf("Second count:%d\n",ret);
	 printf("a=%d b=%d c=%d\n",a,b,c);
	return 0;
}
