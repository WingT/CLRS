/*
 * merge.c
 *
 *  Created on: Feb 12, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 32767
int minheapify(int **tmp,int i,int heapsize)
{
	int min,*t;
	while (1)
	{
		min=i;
		if (i*2<=heapsize)
			min=*tmp[i]<*tmp[i*2]?i:i*2;
		if (i*2+1<=heapsize)
			min=*tmp[min]<*tmp[i*2+1]?min:i*2+1;
		if (min==i)
			break;
		else
		{
			t=tmp[i];
			tmp[i]=tmp[min];
			tmp[min]=t;
			i=min;
		}
	}
	return 0;
}
int buildminheap(int **tmp,int k)
{
	int i;
	for (i=k/2;i>=1;i--)
		minheapify(tmp,i,k);
	return 0;
}
int merge(int **num,int k,int s,int *result)
{
	int **tmp,i;
	tmp=(int **)malloc(sizeof(int*)*(k+1));
	for (i=1;i<=k;i++)
		tmp[i]=num[i-1];
	buildminheap(tmp,k);
	for (i=0;i<s;i++)
	{
		result[i]=*tmp[1];
		tmp[1]++;
		minheapify(tmp,1,k);
	}
	return 0;
}
int main(void)
{
	int k,**num,*result;
	scanf("%d",&k);
	num=(int **)malloc(sizeof(int *)*k);
	int s=0,n,i,j;
	for (i=0;i<k;i++)
	{
		scanf("%d",&n);
		num[i]=(int *)malloc(sizeof(int)*(n+1));
		for (j=0;j<n;j++)
			scanf("%d",num[i]+j);
		*(num[i]+n)=max;
		s+=n;
	}
	result=(int *)malloc(sizeof(int)*s);
	merge(num,k,s,result);
    for (i=0;i<s;i++)
    	printf("%d ",result[i]);
	return 0;
}
