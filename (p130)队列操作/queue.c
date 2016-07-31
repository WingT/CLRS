/*
 * queue.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 5
struct queue{
	int q[max];
	int head;
	int n;
};
int deque(struct queue *q)
{
	if (q->n==0)
	{
		printf("Underflow!\n");
		return 0;
	}
	else
	{
		printf("%d\n",q->q[q->head]);
		q->head=(q->head+1)%max;
		(q->n)--;
		return 0;
	}
}
int enque(struct queue *q)
{
	int tmp;
	if (q->n==max)
	{
		printf("Overflow!\n");
		return 0;
	}
	else
	{
		scanf("%d",&tmp);
		(q->n)++;
		q->q[(q->head+q->n-1)%max]=tmp;
		return 0;
	}
}
int main(void)
{
	struct queue *q;
	int n;
	q=(struct queue *)malloc(sizeof(struct queue));
	q->n=0;
	scanf("%d",&n);
	while (n!=-1)
	{
		switch(n)
		{
		case 0:deque(q);break;
		case 1:enque(q);break;
		default:break;
		}
		scanf("%d",&n);
	}
	return 0;
}

