/*
 * count.c
 *
 *  Created on: Feb 1, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int merge(int *num,int l,int r)
{
	int *tmp=(int *)malloc(sizeof(int)*(r-l+1)),i=l,m=(l+r)/2,j=m+1,k=0,count=0;
	while (i<=m||j<=r)
		if(i<=m&&(j>r||num[i]<=num[j]))
		{
			tmp[k]=num[i];
			k++;
			i++;
		}/*如果j>r那么之前肯定就已经出现过下面的情况，不用重复计算*/
		else
		{
			tmp[k]=num[j];
			k++;
			j++;
			if(i<=m)
				count+=m-i+1;
		}
	for (k=l;k<=r;k++)
		num[k]=tmp[k-l];
	return count;
}
int sort(int *num,int l,int r)
{
	if (l==r)
		return 0;
	else
		return sort(num,l,(l+r)/2)+sort(num,(l+r)/2+1,r)+merge(num,l,r);
}
int main(void)
{
	int n,*num,i;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	printf("%d",sort(num,0,n-1));
	return 0;
}

