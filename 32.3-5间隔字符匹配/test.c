#include<stdio.h>
typedef struct {
	int q[100];
}s;
int comput(s *a)
{	
	int i;
	for (i=0;i<100;i++)
		a->q[i]=i;
	return 0;
}
int main(void)
{
	s a;
	comput(&a);
	int i;
	for (i=0;i<100;i++)
		printf("%d ",a.q[i]);
	return 0;
}
