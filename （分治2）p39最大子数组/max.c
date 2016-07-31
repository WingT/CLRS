/*
 * max.c
 *
 *  Created on: Feb 4, 2016
 *      Author: wing
 */
/*
 * test.c
 *
 *  Created on: 2016年1月21日
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int smax(int *num,int l,int r,int *maxi,int *maxj)
{
	int maxl=0,maxr=0,i,j,m=(l+r)/2,tmp;
	tmp=0;
	for (j=m;j<=r;j++)
		{
			tmp+=num[j];
			if (maxr<tmp)
			{
				maxr=tmp;
				*maxj=j;
			}
		}
	tmp=0;
	for (i=m;i>=l;i--)
		{
			tmp+=num[i];
			if (maxl<tmp)
			{
				maxl=tmp;
				*maxi=i;
			}
		}
	return maxl+maxr-num[m];
}
int max(int a,int b)
{
	return a>b?a:b;
}
int find(int *num,int l,int r)
{
	int *maxi,*maxj,maxl,maxr,maxm;
	if (l==r)
		return num[l];
	maxi=(int *)malloc(sizeof(int));
	maxj=(int *)malloc(sizeof(int));
	maxl=find(num,l,(l+r)/2);
	maxr=find(num,(l+r)/2+1,r);
	maxm=smax(num,l,r,maxi,maxj);
	return max(max(maxl,maxr),maxm);
}
int main(void)
{
	int *num,i,n;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	printf("%d",find(num,0,n-1));
	return 0;
}



