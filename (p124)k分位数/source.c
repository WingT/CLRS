/*
 * source.c
 *
 *  Created on: Feb 16, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int Select(int *num,int m,int l,int r)
{
	int i,j=l-1,tmp;
	if (l==r)
		return num[l];
	for (i=l;i<=r-1;i++)
		if (num[i]<num[r])
		{
			j++;
			tmp=num[j];
			num[j]=num[i];
			num[i]=tmp;
		}
	j++;
	tmp=num[j];
	num[j]=num[r];
	num[r]=tmp;
	if (m-1==j)
		return num[j];
	else
		if (m-1<j)
			return Select(num,m,l,j-1);
		else
			return Select(num,m,j+1,r);
}
int find(int *num,int k,int l,int r,int *result)
{
	result[(l+r)/2]=Select(num,((l+r)/2+1)*k,l*k,(r+2)*k-1);
	if (l==r)
		return 0;
	else
	{
		find(num,k,l,(l+r)/2,result);
		find(num,k,(l+r)/2+1,r,result);
		return 0;
	}
}
int main(void)
{
	int *num,n,k,i,*result;
	scanf("%d",&n);
	scanf("%d",&k);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	result=(int *)malloc(sizeof(int)*k);
	find(num,n/k,0,k-2,result);
	for (i=0;i<=n/k-2;i++)
		printf("%d ",result[i]);
	return 0;
}

