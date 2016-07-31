/*
 * source.c
 *
 *  Created on: Feb 25, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
struct node{
	char n;
	struct node *l,*r;
};
int build(struct node **parent)
{
	char n;
	scanf("%c",&n);
	if (n=='#')
	{
		*parent=NULL;
		return 0;
	}
	else
	{
		*parent=(struct node*)malloc(sizeof(struct node));
		(*parent)->n=n;
		build(&((*parent)->l));
		build(&((*parent)->r));
		return 0;
	}
}
int trav(struct node*parent)
{
	if (parent==NULL)
		return 0;
	printf("%c ",parent->n);
	trav(parent->l);
	trav(parent->r);
}
int main(void)
{
	struct node **root;
	root=(struct node**)malloc(sizeof(struct node*));
	build(root);
	trav(*root);
	return 0;
}

