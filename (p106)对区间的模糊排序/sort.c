/*
 * sort.c
 *
 *  Created on: Feb 13, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
struct line{
	int l;
	int r;
};
int exchange(struct line *x,int i,int j)
{
	struct line tmp;
	tmp=x[i];
	x[i]=x[j];
	x[j]=tmp;
	return 0;
}
int sort(struct line *x,int l,int r)
{
	int i=l-1,j,k=l-1;
	if (r<=l) return 0;
	for (j=l;j<=r-1;j++)
		if (x[j].r<x[r].l)
		{
			exchange(x,k+1,i+1);
			exchange(x,k+1,j);
			i++;
			k++;
		}
		else
			if (x[j].l<=x[r].r)
			{
				exchange(x,i+1,j);
				i++;
			}
	exchange(x, i + 1, r);
	i++;
	sort(x,l,k);
	sort(x,i+1,r);
	return 0;
}
int main(void)
{
	int n,i;
	struct line *x;
	scanf("%d",&n);
	x=(struct line *)malloc(sizeof(struct line)*n);
	for (i=0;i<n;i++)
	{
		scanf("%d",&x[i].l);
		scanf("%d",&x[i].r);
	}
	sort(x,0,n-1);
	for (i=0;i<n;i++)
		printf("(%d,%d) ",x[i].l,x[i].r);
	return 0;
}
