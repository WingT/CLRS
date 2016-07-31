/*
 * source.c
 *
 *  Created on: Mar 4, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 10
int p[max]={1,5,8,9,10,17,17,20,24,30};
int r[max+1];
int MAX(int a,int b)
{
	return a<b?b:a;
}
int cut_rod(int n)
{
	int tmp=0,i;
	if (n==0)
		return 0;
	if (r[n]>0)
		return r[n];
	else
	{
		for (i=1;i<=n;i++)
			tmp=MAX(tmp,p[i-1]+cut_rod(n-i));
		r[n]=tmp;
		return r[n];
	}
}
int cutrod2(int n)
{
	int i,j,tmp;
	for (j=1;j<=max;j++)
	{
		tmp=0;
		for (i=0;i<j;i++)
			tmp=tmp>r[i]+p[j-i-1]?tmp:r[i]+p[j-i-1];
		r[j]=tmp;
	}
	return r[max];
}
int main(void)
{
	int i;
	cut_rod(max);
	for (i=1;i<=max;i++)
		printf("%d ",r[i]);
	printf("\n");
	for (i=0;i<=max;i++)
		r[i]=0;
	cutrod2(max);
	for (i=1;i<=max;i++)
		printf("%d ",r[i]);
	return 0;
}
