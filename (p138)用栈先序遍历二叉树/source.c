/*
 * source.c
 *
 *  Created on: Feb 24, 2016
 *      Author: wing
 */
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
struct stack{
	struct node s[max];
	int top;
};
int push(struct stack *st,struct node *p)
{
	if (st->top==max-1)
	{
		printf("Stack overflow!");
		return 0;
	}
	(st->top)++;
	st->s[st->top]=*p;
	return 0;
}
int pop(struct stack *st)
{
	if (st->top==-1)
	{
		printf("Stack underflow!");
		return 0;
	}
	(st->top)--;
	return 0;
}
int presearch(struct node *root)
{
	struct stack st;
	struct node *tmp=root;
	st.top=-1;
	printf("%d ",tmp->n);
	push(&st,tmp);
	while (st.top>=0)
	{
		tmp=st.s[st.top].l;
		while (tmp!=NULL)
		{
			printf("%d ",tmp->n);
			push(&st,tmp);
			tmp=st.s[st.top].l;
		}
		tmp=st.s[st.top-1].r;
		pop(&st);
		pop(&st);
		if (tmp!=NULL)
			push(&st,tmp);
		else
			tmp=st.s[st.top].r;
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
	presearch(root+1);
	return 0;
}




