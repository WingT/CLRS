/*
 * sort.c
 *
 *  Created on: Jan 31, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int main(void)
{
	int n,*num,i,j,m;
	scanf("%d",&n);
	num=(int *)malloc(sizeof(int)*n);
	for (i=0;i<n;i++)
		scanf("%d",num+i);
    for (i=1;i<=n-1;i++)
    {
    	m=num[i];
    	j=i-1;
    	while (j>=0&&m<num[j])
    	{
    		num[j+1]=num[j];
    		j--;
    	}
    	num[j+1]=m;
    }
    for (i=0;i<n;i++)
    	printf("%d ",num[i]);
	return 0;
}

