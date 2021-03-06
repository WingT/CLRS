/*
 * sort.c
 *
 *  Created on: Feb 14, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int figk(int n)
{
	int c=0;
	while (n!=0)
	{
		c++;
		n=n/10;
	}
	return c;
}
int getdigit(int n,int k)
{
	int i;
	for (i=1;i<k;i++)
		n/=10;
	return n%10;
}
int digitsort(int *num,int k,int n,int *result)
{
	int i,tmp[10];
	for (i=0;i<10;i++)
		tmp[i]=0;
	for (i=1;i<=n;i++)
		tmp[getdigit(num[i],k)]++;
	for (i=1;i<=9;i++)
		tmp[i]+=tmp[i-1];
	for (i=n;i>0;i--)
	{
		result[tmp[getdigit(num[i],k)]]=num[i];
		tmp[getdigit(num[i],k)]--;
	}
	return 0;
}
int main(void)
{
	int *num,n,i,maxk=0,k,*result,*p;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*(n+1));
	result=(int *)malloc(sizeof(int)*(n+1));
	for (i=1;i<=n;i++)
	{
		scanf("%d",&num[i]);
		maxk=figk(num[i])>maxk?figk(num[i]):maxk;
	}
	for (k=1;k<=maxk;k++)
	{
		digitsort(num,k,n,result);
		p=num;
		num=result;
		result=p;
	}
	for (i=1;i<=n;i++)
		printf("%d ",num[i]);
	return 0;
}

