/*
 * source.c
 *
 *  Created on: Feb 17, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int Select(int *a,int *b,int n,int l,int r,int *result)
{
	int m=(l+r)/2;
	if (b[n-m-2]<=a[m]&&a[m]<=b[n-m-1])
	{
		*result=a[m];
		return 1;
	}
	else
		if (l>=r)
			return 0;
		else
			if (a[m]<b[n-m-2])
				return Select(a,b,n,m+1,r,result);
			else
				if (a[m]>b[n-m-1])
					return Select(a,b,n,l,m-1,result);
}
int main(void)
{
	int *a,*b,n,i,*result;
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int)*n);
	b=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&a[i]);
	for (i=0;i<n;i++)
		scanf("%d",&b[i]);
	result=(int *)malloc(sizeof(int));
	if (Select(a,b,n,0,n-1,result))
		printf("%d",*result);
	else
		if (Select(b,a,n,0,n-1,result))
			printf("%d",*result);
	return 0;
}

