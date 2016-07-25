#include<stdio.h>
#define max 100
int LS(int a[],int f[],int d[],int next[],int n)
{
	int i,j;
	f[0]=1;
	for (i=1;i<n;i++)
		f[i]=0;//初始化值<=1都可以
	d[0]=0;
	for (i=0;i<n;i++)
	{
		for (j=0;j<i;j++)
			if (a[i]>=a[d[j]])
			{
				f[i]=f[j]+1>f[i]?(next[i]=j,f[j]+1):f[i];
				d[i]=i;
			}
			else
			{
				f[i]=f[j]>f[i]?(d[i]=d[j],next[i]=j,f[j]):f[i];
			}
	}
	return f[n-1];
}
int printLS(int a[],int next[],int d[],int n)
{
	int l=n;
	if (d[l]==l)
		printf("%d ",a[l]);
	while (1)
	{
		printf("%d ",a[next[l]]);
		if (d[l]==1)
			break;
		l=next[l];
	}
	printf("\n");
	return 0;
}
int main(void)
{
	int a[max]={8,34,11,39,0,27,56,42,95,56,13},f[max],d[max],next[max],n=11,ans;/*next为跳转表，用来构建LS，需要注意的是，对于前面的元素均比自己大的情况已经是LS的开头*/	
	ans=LS(a,f,d,next,n);
	printf("%d\n",f[n-1]);
	int i;
	for (i=0;i<n;i++)
		printf("%d ",f[i]);
	printf("\n");
	for (i=0;i<n;i++)
		printf("%d ",d[i]);
	printf("\n");
	printLS(a,next,d,n-1);
	return 0;
}
