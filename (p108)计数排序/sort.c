/*
 * sort.c
 *
 *  Created on: Feb 14, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(void)
{
	int *num,*tmp,n,i,max=0,*result;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	result=(int *)malloc(sizeof(int)*(n+1));
	for (i=0;i<n;i++)
	{
		scanf("%d",&num[i]);
		if (max<num[i])
			max=num[i];
	}
	tmp=(int *)malloc(sizeof(int)*(max+1));
	memset(tmp,0,sizeof(int)*(max+1));
	for (i=0;i<n;i++)
		tmp[num[i]]++;
	for (i=1;i<=max;i++)
		tmp[i]+=tmp[i-1];
	for (i=n-1;i>=0;i--)/*只有downto这样才是稳定的*/
	{
		result[tmp[num[i]]]=num[i];
		tmp[num[i]]--;
	}
	for (i=1;i<=n;i++)
		printf("%d ",result[i]);
	return 0;
}

