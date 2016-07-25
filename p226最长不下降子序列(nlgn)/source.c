#include<stdio.h>
#define max 1000
int biSearch(int d[],int x,int l,int r)
{
	int m=(l+r)/2;
	if (x>=d[r])
		return r;
	if ((r-l)==1)
		return l;
	if (x>=d[m])
		return biSearch(d,x,m,r);
	else
		return biSearch(d,x,l,m-1);
}
int LS(int x[],int d[],int n)
{
	int i,k=1,tmp;
	d[0]=0x80000000;
	d[1]=x[0];
	for (i=1;i<n;i++)
		if (x[i]>=d[k])
			d[++k]=x[i];
		else
		{
			tmp=biSearch(d,x[i],0,k-1);
			d[tmp+1]=x[i];
		}
	return k;
}
int main(void)
{
	int x[max]={33,123,55,3,78,54,32,67,4,29},n=10,d[max+1],ans;
	ans=LS(x,d,n);
	printf("%d\n",ans);
	int i;
	for (i=1;i<=n;i++)
		printf("%d ",d[i]);
	printf("\n");
	return 0;
}
