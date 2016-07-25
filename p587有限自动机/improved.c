#include<stdio.h>
#include<string.h>
#define maxn 1000
#define maxm 100
int dt[maxm+1][26],f[maxm+1];
int computf(char p[])
{
	int i,m=strlen(p);
	f[1]=0;
	int k=0;
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
int computdt(char p[])
{
	int q,m=strlen(p);
	char a;
	for  (q=0;q<=m;q++)
		for (a='a';a<'z';a++)
		{
			int k=q;
			while (k>0&&p[k]!=a)
				k=f[k];
			if (p[k]==a)
				k++;
			dt[q][(int)(a-'a')]=k;
		}
	return 0;
}
int match(char t[],char p[])
{
	int n=strlen(t),m=strlen(p),i,q=0;
	for (i=0;i<n;i++)
	{
		q=dt[q][(int)(t[i]-'a')];
		if (q==m)
			printf("%d ",i-m+1);
	}
	return 0;
}
int main(void)
{
	char t[maxn],p[maxm];
	scanf("%s",t);
	scanf("%s",p);
	computf(p);
	computdt(p);
	match(t,p);
	return 0;
}
