#include<stdio.h>
int euclid(int a,int b,int *x,int *y)
{
	if (b==0)
	{
		*x=1;
		*y=0;
		return a;
	}
	else
	{
		int d;
		d=euclid(b,a%b,x,y);
		int tmp;
		tmp=*x;
		*x=*y;
		*y=tmp-(a/b)*(*y);
		return d;
	}
}
int main(void)
{
	int a,b,x,y;
	scanf("%d%d",&a,&b);
	int d;
	d=euclid(a,b,&x,&y);
	printf("%d=%d*%d+%d*%d\n",d,a,x,b,y);
	return 0;
}
