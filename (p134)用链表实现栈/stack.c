/*
 * stack.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
struct node{
	int n;
	struct node *next;
	struct node *prev;
};
int pop(struct node **s)
{
	if (*s==NULL)
	{
		printf("Stack underflow!\n");
		return 0;
	}
	else
	{
		printf("%d\n",(*s)->n);
		if ((*s)->next==NULL)
		{
			free(*s);
			*s=NULL;
		}
		else
		{
			*s=(*s)->next;
			free((*s)->prev);
			(*s)->prev=NULL;
		}
		return 0;
	}
}
int push(struct node **s)
{
	struct node *new;
	int n;
	new=(struct node *)malloc(sizeof(struct node));
	scanf("%d",&n);
	new->n=n;
	new->next=*s;
	new->prev=NULL;
	if ((*s)!=NULL)
		(*s)->prev=new;
	*s=new;
	return 0;
}
int main(void)
{
	int n;
	struct node **s;
	s=(struct node **)malloc(sizeof(struct node *));
	*s=NULL;
	scanf("%d",&n);
		while (n!=-1)
		{
			switch(n)
			{
			case 0:pop(s);break;
			case 1:push(s);break;
			default:break;
			}
			scanf("%d",&n);
		}
		return 0;
}

