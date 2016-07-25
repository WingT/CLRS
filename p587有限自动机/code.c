#include<stdio.h>
#include<string.h>
#define maxn 1000
#define maxm 100
int f[maxm+1][26];
int is_suffix(char p[],int k,int q,char a)
{
	int i;
	if (k==0)
		return 1;
	if (p[k-1]!=a)
		return 0;
	for (i=0;i<k-1;i++)
		if (p[i]!=p[q-k+1+i])
			return 0;
	return 1;
}
int comf(char p[],int m)
{
	int q,k;
	for (q=0;q<=m;q++)
	{
		char a;
		for (a='a';a<='z';a++)
		{
			k=q+1<=m?q+1:m;
			while (!is_suffix(p,k,q,a))
				k--;
			f[q][(int)(a-'a')]=k;
		}
	}
	return 0;
}
int match(char t[],char p[],int n,int m)
{
	int q=0,i;
	for (i=0;i<n;i++)
	{
		q=f[q][(int)(t[i]-'a')];
		if (q==m)
			printf("%d\n",i-m+1);
	}
	return 0;
}
int main(void)
{
	char t[maxn],p[maxm];
	int n,m;
	scanf("%s",t);
	scanf("%s",p);
	n=strlen(t);
	m=strlen(p);
	comf(p,m);
	match(t,p,n,m);
	return 0;
}
