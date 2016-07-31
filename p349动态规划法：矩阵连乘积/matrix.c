/*
 * matrix.c
 *
 *  Created on: 2016年1月21日
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
int **s;
int matrixchain(int *p,int n,int **m,int **s)
{
	int r,i,k,mink,min,tmp;
	for (i=1;i<=n;i++)
		m[i][i]=0;
	for (r=2;r<=n;r++)
		for(i=1;i<=n-r+1;i++)
		{
			min=32767;
			for (k=i;k<=i+r-2;k++)
			{
				tmp=m[i][k]+m[k+1][i+r-1]+p[i-1]*p[k]*p[i+r-1];
				if (tmp<min)
				{
					min=tmp;
					mink=k;
				}
			}
			m[i][i+r-1]=min;
		    s[i][i+r-1]=mink;
		}
	return 0;
}
int traceback(int i,int j)
{
	if (i==j)
		printf("M%d",i);
	else
	{
		printf("(");
		traceback(i,s[i][j]);
		traceback(s[i][j]+1,j);
		printf(")");
	}
	return 0;
}
int  main(void)
{
    int n,i,*p,**m;
    scanf("%d",&n);
    p=(int *)malloc(sizeof(int)*(n+1));
    for (i=0;i<n+1;i++)
    	scanf("%d",p+i);
    m=(int **)malloc(sizeof(int *)*(n+1));
    s=(int **)malloc(sizeof(int *)*(n+1));
    for (i=0;i<n+1;i++)
    {
    	m[i]=(int *)malloc(sizeof(int)*(n+1));
    	s[i]=(int *)malloc(sizeof(int)*(n+1));
    }
    matrixchain(p,n,m,s);
    printf("%d\n",m[1][n]);
    traceback(1,n);
	return 0;
}
