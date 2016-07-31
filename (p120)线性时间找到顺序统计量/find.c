/*
 * find.c
 *
 *  Created on: Feb 15, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int exchange(int *num,int i,int j)
{
	int tmp;
	tmp=num[i];
	num[i]=num[j];
	num[j]=tmp;
	return 0;
}
int find(int *num,int k,int l,int r)
{
	int i=l-1,j;
	if (l==r)return num[l];
	exchange(num,rand()%(r-l)+l,r);
	for (j=l;j<r;j++)
		if (num[j]<=num[r])
		{
			i++;
			exchange(num,i,j);
		}
	exchange(num,i+1,r);
	if (i+1==k-1) return num[i+1];
	else
		if (i+1>k-1)
			return find(num,k,l,i);
		else
			return find(num,k,i+2,r);
}
int main(void)
{
	int n,i,k,*num;
	time_t t;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	scanf("%d",&k);
	srand((unsigned int)time(&t));
	printf("%d",find(num,k,0,n-1));
	return 0;
}

