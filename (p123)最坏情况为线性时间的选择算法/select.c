/*
 * select.c
 *
 *  Created on: Feb 16, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int sort(int *num,int l,int r)
{
	int i,j,x;
	for (i=l+1;i<=r;i++)
	{
		x=num[i];
		j=i-1;
		while(j>=l&&num[j]>x)
		{
			num[j+1]=num[j];
			j--;
		}
		num[j+1]=x;
	}
	return num[(l+r)/2];
}
int find(int *num,int k,int n,int l,int r)
{
	if (l==r)return num[l];
	int i,*tmp,mid,j,t;
	tmp=(int *)malloc(sizeof(int)*((int)ceil(n/5.0)));
	for (i=1;i<=n/5;i++)
		tmp[i-1]=sort(num,l+(i-1)*5,l+i*5-1);
	if (n%5)
		tmp[i-1]=sort(num,l+(i-1)*5,l+n-1);
	mid=find(tmp,(int)ceil(ceil(n/5.0)/2),(int)ceil(n/5.0),0,(int)ceil(n/5.0)-1);
	j=l-1;
	for (i=l;i<=r;i++)
		if (num[i]<=mid)
		{
			j++;
			t=num[j];
			num[j]=num[i];
			num[i]=t;
		}
	if (k-1==j)
		return mid;
	else
		if (k-1<j)
			return find(num,k,j-l+1,l,j);
		else
			return find(num,k,r-j,j+1,r);
};
int main(void)
{
	int *num,i,n,k,a;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	scanf("%d",&k);
	a=find(num,k,n,0,n-1);
	printf("%d",a);
	return 0;
}
