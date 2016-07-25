#include<stdio.h>
#define maxn 100
#define maxw 1000
int w[maxn+1]={0,10,20,30},v[maxn+1]={0,60,100,120},d[maxn+1][maxw+2],n=3,W=50,ans;
int select(int w[],int v[],int n,int W)
{
	int i,j,f[maxn+1][maxn+1];
	for (i=0;i<=n;i++)
		for (j=0;j<=W;j++)
		{
			f[i][j]=0;
			d[i][j]=0;
		}
	for (i=1;i<=n;i++)
		for (j=0;j<=W;j++)
		{
			f[i][j]=f[i-1][j];
			d[i][j]=d[i-1][j];
			if ((w[i]<=j)&&(f[i-1][j-w[i]]+v[i]>f[i][j]))
			{
				f[i][j]=f[i-1][j-w[i]]+v[i];
				d[i][j]=i;
			}
		}
	return f[n][W];
}
int print(int d[][maxw+2],int i,int j)
{
	while (i>=1)
	{
		if (i==d[i][j])
		{
			printf("%d ",i);
			j-=w[i];
			i=d[i-1][j];
		}
		else
			i=d[i-1][j];
	}
	printf("\n");
	return 0;
}
int main(void)
{
	ans=select(w,v,n,W);
	printf("%d\n",ans);
	print(d,n,W);
	return 0;
}
