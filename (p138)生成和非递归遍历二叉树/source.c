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
	struct node *l,*r;
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
		build(&(*parent)->r);
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
	struct node *next;
	struct stack st;
	initstack(&st);
	next=root;
	while (next!=NULL||st.top>=0)
	{
		if (next!=NULL)
		{
			printf("%c ",next->n);
			push(&st,next);
			next=next->l;
		}
		else
		{
			next=pop(&st);
			next=next->r;
		}
	}
	free(st.head);
	return 0;
}
int intrav(struct node *root)
{
	struct stack st;
	struct node *next;
	initstack(&st);
	next=root;
	while (next!=NULL||st.top>=0)
	{
		if (next!=NULL)
		{
			push(&st,next);
			next=next->l;
		}
		else
		{
			next=pop(&st);
			printf("%c ",next->n);
			next=next->r;
		}
	}
	free(st.head);
	return 0;
}
int postrav(struct node *root)
{
	struct node *next,*prev;/*next存放将要如栈的指针，prev存放刚刚出栈的指针*/
	struct stack st;
	initstack(&st);
	next=root;
	while (next!=NULL||st.top>=0)
	{
		while(next!=NULL)
		{
			push(&st,next);
			next=next->l;
		}
		prev=NULL;/*将空节点视为刚刚出栈的元素*/
		while (st.top>=0)
		{
			next=st.head[st.top];
			if (next->r==prev)/*如果刚出栈的是右孩子，则该节点可以出栈*/
			{
				printf("%c ",next->n);
				prev=pop(&st);
			}
			else
			{
				next=next->r;/*如果刚刚出栈的不是右孩子，则该节点暂时不能出栈，将右孩子入栈*/
				break;
			}
		}
		if (st.top==-1)/*最后一次出栈的时候，top为-1，但是next是指向根节点的指针，因此需要判断一下*/
			break;
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
	printf("\n中序遍历：");
	intrav(*root);
	printf("\n后序遍历：");
	postrav(*root);
	return 0;
}

