#include<stdio.h>
#include<stdlib.h>
#define max 1000
float v[max+1]={0,60,100,120};
int w[max+1]={0,10,20,30},W=50,n=3;
struct item{
	float vpw;
	int i;
};
int swap(struct item m[],int a,int b)
{
	struct item tmp;
	tmp=m[a];
	m[a]=m[b];
	m[b]=tmp;
	return 0;
}
int partition(struct item m[],int l,int r,int *j,int *k)
{
	int mid=(l+r)/2,i,tj=l-1,tk=l-1;
	float x=m[mid].vpw;
	for (i=l;i<=r;i++)
		if (m[i].vpw>x)
		{
			tj++;
			tk++;
			swap(m,tj,tk);
			swap(m,tj,i);
		}
		else
			if (m[i].vpw==x)
			{
				tk++;
				swap(m,tk,i);
			}
	*j=tj;
	*k=tk;
	return 0;
}
float Select(struct item m[],int W,int l,int r)
{
	if (l==r)
		return l;
	int j,k;
	partition(m,l,r,&j,&k);	
	int i,sj=0,sk=0,sr=0;
	for (i=l;i<=j;i++)
		sj+=w[m[i].i];
	sk=sj;
	for (i=j+1;i<=k;i++)
		sk+=w[m[i].i];
	sr=sk;
	for (i=k+1;i<=r;i++)
		sr+=w[m[i].i];
	if (W>sr)
		return r;
	else
		if (W>sk)
			return Select(m,W-sk,k+1,r);
		else
			if (W>sj)
				return Select(m,W-sj,j+1,k);
			else
				return Select(m,W,l,j);
}
int main(void)
{
	struct item m[max+1];
	int i;
	for (i=1;i<=n;i++)
	{
		m[i].vpw=v[i]/w[i];
		m[i].i=i;
	}
	int l;
	l=Select(m,W,1,n);
	float sv=0;
	int sw=0;
	for (i=1;i<l;i++)
	{
		sv+=v[m[i].i];
		sw+=w[m[i].i];
	}
	if (sw+w[m[i].i]>W)
		sv+=(W-sw+0.0)/w[m[i].i]*v[m[i].i];
	else
		sv+=v[m[i].i];
	printf("%f\n",sv);
	return 0;
}
