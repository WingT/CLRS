/*
 * source.c
 *
 *  Created on: Feb 25, 2016
 *      Author: wing
 */
/*
 * source.c
 *
 *  Created on: Feb 25, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define maxsize 1000
struct node{
	char n;
	struct node *p,*l,*r;
};
struct stack{
	struct node **head;
	int top;
};
int build(struct node **parent)/*递归建立二叉树*/
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
		*parent=(struct node *)malloc(sizeof(struct node));
		(*parent)->n=n;
		build(&(*parent)->l);
		if ((*parent)->l!=NULL)
			(*parent)->l->p=*parent;
		build(&(*parent)->r);
		if ((*parent)->r!=NULL)
					(*parent)->r->p=*parent;
		return 0;
	}
}
int initstack(struct stack *st)
{
	st->head=(struct node**)malloc(sizeof(struct node*)*(maxsize));
	st->top=-1;
	return 0;
}
int push(struct stack *st,struct node *next)
{
	st->head[++(st->top)]=next;
	return 0;
}
struct node *pop(struct stack *st)
{
	return st->head[st->top--];
}
int pretrav(struct node *root)
{
	struct node *next=root;
	int dir=1;
	while (next!=NULL)
	{
		if(dir==1)
		{
			printf("%c",next->n);
			if (next->l!=NULL)
			{
				next=next->l;
				dir=1;
			}
			else
				if (next->r!=NULL)
				{
					next=next->r;
					dir=1;
				}
				else
				{
					if (next->p==NULL)
					{
						next==NULL;
						break;
					}
					if (next==next->p->l)
						dir=2;
					else
						dir=3;
					next=next->p;
				}
		}
		if (dir==2)
			if (next->r!=NULL)
			{
				next=next->r;
				dir=1;
			}
			else
			{
				if (next->p==NULL)
				{
					next=NULL;
					break;
				}
				if (next==next->p->l)
					dir=2;
				else
					dir=3;
				next=next->p;
			}
		if (dir==3)
		{
			if (next->p==NULL)
			{
				next=NULL;
				break;
			}
			if (next==next->p->l)
				dir=2;
			else
				dir=3;
			next=next->p;
		}
	}
	return 0;
}
int main(void)
{
	struct node **root;
	root=(struct node **)malloc(sizeof(struct node*));
	build(root);
	printf("先序遍历：");
	pretrav(*root);
	return 0;
}
