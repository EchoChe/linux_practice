# include <stdio.h>
int main()
{
	int a = 0;
	int b = 0;
	int c = 0;
	int ret = 0;
	
	ret = scanf("%d%d%d",&a,&b,&c);
	printf("\nfirst counts:%d\n",ret);
	printf("\na=%d b=%d c=%d ",a,b,c);

	ret = scanf("%d%d%d",&a,&b,&c);
	printf("\nsecond counts:%d\n",ret);
	printf("\na=%d b=%d c=%d \n",a,b,c);
	return 0;
}
