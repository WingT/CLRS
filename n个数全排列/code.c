/*
 * code.c
 *
 *  Created on: 2016年1月21日
 *      Author: wing
 */
#include<stdio.h>
int n,p[100],s[100];
int search(int k)
{
	int i;
	if (k==n+1)
	{
		for (i=1;i<=n;i++)
			printf("%d ",s[i]);
		printf("\n");
		return 0;
	}
	else
	{
		for (i=1;i<=n;i++)
			if (!p[i])
			{
				p[i]=1;
				s[k]=i;
				search(k+1);
				p[i]=0;
			}
		return 0;
	}
}
int main(void)
{
	scanf("%d",&n);
	search(1);
	return 0;
}

