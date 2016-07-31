/*
 * source.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 10
struct node{
	int n;
	struct node *p,*l,*r;
};
int possearch(struct node*bt)
{
	struct node *st[max],*p;
	int top=-1;
	/*if(bt!=NULL)
	{
		do{*/
	while (bt!=NULL||top>=0)
	{
			while(bt!=NULL)
			{
				top++;
				st[top]=bt;
				bt=bt->l;
			}
			p=NULL;
			while(top!=-1)
			{
				bt=st[top];
				if(bt-> r==p)
				{
					printf("%d ",bt->n);
					top--;
					p=bt;
				}
				else
				{
					bt=bt->r;
					break;
				}
			}
			if (top==-1)
				break;
	}/*while(top!=-1);*/
	/*}*/
	return 0;
}
int build(struct node *root,int n)/*由一个x[i]=i的数组建立二叉树，方法和建堆的方法一样*/
{
	int i;
	for (i=1;i<=n;i++)
		root[i].n=i;
	for (i=1;i<=n;i++)
	{
		root[i].p=root+i/2;
		if (i*2<=n)
			root[i].l=root+i*2;
		else
			root[i].l=NULL;
		if (i*2+1<=n)
			root[i].r=root+i*2+1;
		else
			root[i].r=NULL;
	}
	return 0;
}
int main(void)
{
	struct node *root;
	root=(struct node *)malloc(sizeof(struct node)*(max+1));
	build(root,max);
	possearch(root+1);
	return 0;
}


