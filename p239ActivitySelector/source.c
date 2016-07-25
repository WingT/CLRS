#include<stdio.h>
#include<limits.h>
#define max 1000
int GreedyActivitySelector(int s[],int f[],int ans[],int n)
{
	int k=0,i,count=0;
	for (i=1;i<=n;i++)
		if (s[i]>=f[k])
		{
			ans[count++]=i;
			k=i;
		}
	return count;
}
int ActivitySelector(int s[],int f[],int ans[],int k,int n,int *count)
{
	int i=k+1;
	while ((i<=n)&&(s[i]<f[k]))
		i++;
	if (i<=n)
	{
		ans[(*count)++]=i;
		ActivitySelector(s,f,ans,i,n,count);
	}
	return 0;
}
int ActivitySelector2(int s[],int f[],int n)
{
	int i,j,k,l;
	int c[max+2][max+2];
	for (i=0;i<=n+1;i++)
		for (j=0;j<=n+1;j++)
			c[i][j]=0;
	for (l=0;l<=n+1;l++)
		for (i=0;i<=n+1-l;i++)
		{
			j=i+l;
			for (k=i+1;k<=j-1;k++)
				if ((s[k]>=f[i])&&(f[k]<=s[j])&&(c[i][k]+c[k][j]+1>c[i][j]))
						c[i][j]=c[i][k]+c[k][j]+1;
		}
	for (j=0;j<=n+1;j++)
		printf("%3d ",j);
	printf("\n");
	for (i=0;i<=n+1;i++)
	{
		for (j=0;j<i;j++)
			printf("    ");
		for (j=i;j<=n+1;j++)
			printf("%3d ",c[i][j]);
		printf("%3d\n",i);
		printf("\n");
	}
	return c[0][n+1];
}
int main(void)
{
	int f[max+2]={0,4,5,6,7,9,9,10,11,12,14,16};
	int s[max+2]={0,1,3,0,5,3,5,6,8,8,2,12};
	int ans[max];
	int count;
	int n=11;
	count=GreedyActivitySelector(s,f,ans,n);
	printf("%d\n",count);
	int i;
	for (i=0;i<count;i++)
		printf("%d ",ans[i]);
	count=0;
	ActivitySelector(s,f,ans,0,n,&count);
	printf("\n%d\n",count);
	for (i=0;i<count;i++)
		printf("%d ",ans[i]);
	printf("\n");
	s[n+1]=INT_MAX;
	f[n+1]=INT_MAX;
	count=ActivitySelector2(s,f,n);
	printf("\n%3d\n",count);
	return 0;
}
