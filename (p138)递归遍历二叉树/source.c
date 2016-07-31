/*
 * source.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 10/*二叉树节点数目*/
struct node{
	int n;
	struct node *p,*l,*r;
};
int presearch(struct node *p)/*先序遍历*/
{
	printf("%d ",p->n);
	if (p->l!=NULL)
		presearch(p->l);
	if (p->r!=NULL)
		presearch(p->r);
	return 0;
}
int possearch(struct node *p)/*后序遍历*/
{
	if (p==NULL)
		return 0;
	possearch(p->l);
	possearch(p->r);
	printf("%d ",p->n);
	return 0;
}
int insearch(struct node *p)/*中序遍历*/
{
	if (p==NULL)
		return 0;
	insearch(p->l);
	printf("%d ",p->n);
	insearch(p->r);
	return 0;
}
int build(struct node *root,int n)/*由一个x[i]=i的数组建立二叉树，方法和建堆的方法一样*/
{
	int i;
	for (i=1;i<=n;i++)
		root[i].n=i;
	for (i=1;i<=n/2;i++)
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
	printf("先序遍历: ");
	presearch(root+1);
	printf("\n后序遍历: ");
	possearch(root+1);
	printf("\n中序遍历: ");
	insearch(root+1);
	return 0;
}

