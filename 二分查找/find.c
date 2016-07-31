/*
 * find.c
 *
 *  Created on: Feb 1, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int find(int *num,int target,int l,int r)
{
	int m=(l+r)/2;
	if (l==r&&num[l]!=target)
		return -1;
	if (num[l]==target)
		return l;
	else
		if(num[r]==target)
			return r;
		else
			if (num[m]==target)
				return m;
			else
				if (target<num[m])
					return find(num,target,l,m);
				else
					return find(num,target,m,r);

}
int main(void)
{
	int *num,i,n,target;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",&num[i]);
	scanf("%d",&target);
	printf("%d",find(num,target,0,n-1));
	return 0;
}

