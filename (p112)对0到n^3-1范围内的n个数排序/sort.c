/*
 * sort.c
 *
 *  Created on: Feb 15, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct num{
	int n;
	int d[3];
};
int digitsort(struct num *x,int j,int n,struct num *result)
{
	int i,*c;
	c=(int *)malloc(sizeof(int)*n);
	memset(c,0,sizeof(int)*n);
	for (i=0;i<n;i++)
		c[x[i].d[j]]++;
	for (i=1;i<n;i++)
		c[i]+=c[i-1];
	for (i=n-1;i>=0;i--)
	{
		result[c[x[i].d[j]]-1]=x[i];
		c[x[i].d[j]]--;
	}
	return 0;
}
int main(void)
{
	struct num *x,*result,*p;
	int n,i,tmp,j;
	scanf("%d",&n);
	x=(struct num*)malloc(sizeof(struct num)*n);
	for (i=0;i<n;i++)
	{
		scanf("%d",&(x[i].n));
		tmp=x[i].n;
		for (j=2;j>=0;j--)
		{
			x[i].d[j]=tmp%n;
			tmp/=n;
		}
	}
	result=(struct num*)malloc(sizeof(struct num)*n);
	for (j=2;j>=0;j--)
	{
		digitsort(x,j,n,result);
		p=x;
		x=result;
		result=p;
	}
	for (i=0;i<n;i++)
		printf("%d ",x[i].n);
	return 0;
}

