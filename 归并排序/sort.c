/*
 * sort.c
 *
 *  Created on: Jan 31, 2016
 *      Author: wing
 */


#include<stdio.h>
#include<stdlib.h>
int merge(int *num,int l,int r)
{
	int *tmp=(int *)malloc(sizeof(int)*(r-l+1)),i=l,m=(l+r)/2,j=m+1,k=0;
	while (i<=m||j<=r)
		if(i<=m&&(j>r||num[i]<=num[j]))
		{
			tmp[k]=num[i];
			k++;
			i++;
		}
		else
		{
			tmp[k]=num[j];
			k++;
			j++;
		}
	for (k=l;k<=r;k++)
		num[k]=tmp[k-l];
        free(tmp);
	return 0;
}
int sort(int *num,int l,int r)
{
	if (l==r)
		return 0;
	else
	{
		sort(num,l,(l+r)/2);
		sort(num,(l+r)/2+1,r);
		merge(num,l,r);
		return 0;
	}
}
int main(void)
{
	int n,*num,i;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	sort(num,0,n-1);
	for (i=0;i<n;i++)
		printf("%d ",num[i]);
	return 0;
}
