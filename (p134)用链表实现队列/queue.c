/*
 * queue.c
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
struct queue{
	struct node *head;
	struct node *tail;
};
int deque(struct queue *q)
{
	if (q->head==NULL)
	{
		printf("Queue underflow!\n");
		return 0;
	}
	else
		if (q->head->next==NULL)
		{
			printf("%d\n",q->head->n);
			free(q->head);
			q->head=NULL;
			q->tail=NULL;
			return 0;
		}
		else
		{
			printf("%d\n",q->head->n);
			q->head=q->head->next;
			free(q->head->prev);
			q->head->prev=NULL;
			return 0;
		}
}
int enque(struct queue *q)
{
	int n;
	struct node *new;
	new=(struct node*)malloc(sizeof(struct node));
	scanf("%d",&n);
	new->n=n;
	if (q->head==NULL)
	{
		q->head=new;
		q->tail=new;
		new->prev=NULL;
		new->next=NULL;
		return 0;
	}
	else
	{
		new->next=NULL;
		new->prev=q->tail;
		q->tail->next=new;
		q->tail=new;
		return 0;
	}

}
int main(void)
{
	int n;
	struct queue q;
	q.head=NULL;
	q.tail=NULL;
	scanf("%d",&n);
	while (n!=-1)
	{
		switch(n)
		{
		case 0:deque(&q);break;
		case 1:enque(&q);break;
		default:break;
		}
		scanf("%d",&n);
	}
	return 0;
}



