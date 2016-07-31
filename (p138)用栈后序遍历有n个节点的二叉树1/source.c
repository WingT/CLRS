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
int possearch(struct node *bt)
{
	struct node*p;
	struct{
		struct node*pt;
		int tag;
	}st[max];
	int top=-1;
	top++;
	st[top].pt=bt;
	st[top].tag=1;
	while(top>-1)/*栈不为空*/
	{
		if(st[top].tag==1)/*不能直接访问的情况*/
		{
			p=st[top].pt;
			top--;
			if(p!=NULL)
			{
				top++;/*根结点*/
				st[top].pt=p;
				st[top].tag=0;
				top++;/*右孩子结点*/
				st[top].pt=p->r;
				st[top].tag=1;
				top++;/*左孩子结点*/
				st[top].pt=p->l;
				st[top].tag=1;
			}
		}
		if(st[top].tag==0)/*直接访问的情况*/
		{
			printf("%d ",st[top].pt->n);
			top--;
		}
	}
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

