#include<stdio.h>
#include<string.h>
#define maxn 1000
#define maxm 100
int f[maxm+1];
int computf(char p[])
{
	int m=strlen(p);
	f[1]=0;
	int k=0,i;
	for (i=2;i<=m;i++)
	{
		while (k>0&&p[k]!=p[i-1])
			k=f[k];
		if (p[k]==p[i-1])
			k++;
		f[i]=k;
	}
	return 0;
}
int matcher(char t[],char p[])
{
	int n=strlen(t),m=strlen(p),i,q;
	q=0;
	for (i=0;i<n;i++)
	{
		while (q>0&&p[q]!=t[i])
			q=f[q];
		if (p[q]==t[i])
			q++;
		if (q==m)
		{
			printf("%d ",i-m+1);
			q=f[q];
		}
	}
	return 0;
}
int main(void)
{
	char t[maxn],p[maxm];
	scanf("%s",t);
	scanf("%s",p);
	computf(p);
	matcher(t,p);
	return 0;
}
