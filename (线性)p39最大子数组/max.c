/*
 * max.c
 *
 *  Created on: Feb 10, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int n,i,*num,cursum=0,maxsum=0,l=0,r;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
	{
		scanf("%d",&num[i]);
		cursum+=num[i];
		if (maxsum<cursum)
		{
			maxsum=cursum;
			r=i;
		}
		if (cursum<0)
		{
			cursum=0;
			l=i+1;
		}
	}
	printf("%d,%d,%d",maxsum,l,r);
	return 0;
}

