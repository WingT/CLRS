/*
 * source.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 5
struct stack{
	int s[max];
	int tail;
};
struct queue{
	struct stack s1;
	struct stack s2;
	int n;
}q;
int flow(struct stack *s1,struct stack *s2,int n)
{
	int i;
	for (i=0;i<n;i++)
		s2->s[i]=s1->s[s1->tail-i];
	s1->tail-=n;
	s2->tail+=n;
	return 0;
}
int deque(void)
{
	if (q.n==0)
	{
		printf("Queue underflow!\n");
		return 0;
	}
	else
		if (q.s2.tail>=0)
		{
			printf("%d\n",q.s2.s[q.s2.tail]);
			q.n--;
			q.s2.tail--;
			return 0;
		}
		else
		{
			flow(&(q.s1),&(q.s2),q.n-1);
			printf("%d\n",q.s1.s[0]);
			q.s1.tail--;
			q.n--;
			return 0;
		}
}
int enque(void)
{
	int tmp;
	if (q.n==max)
	{
		printf("Queue overflow!\n");
		return 0;
	}
	else
		if (q.s2.tail>=0)
		{
			scanf("%d",&tmp);
			flow(&(q.s2),&(q.s1),q.n);
			q.s1.tail++;
			q.s1.s[q.s1.tail]=tmp;
			q.n++;
			return 0;
		}
		else
		{
			scanf("%d",&tmp);
			q.s1.tail++;
			q.s1.s[q.s1.tail]=tmp;
			q.n++;
			return 0;
		}
}
int main(void)
{
	int n;
	scanf("%d",&n);
	q.n=0;
	q.s1.tail=-1;
	q.s2.tail=-1;
	while (n!=-1)
	{
		switch (n)
		{
		case 0:deque();break;
		case 1:enque();break;
		default:break;
		}
		scanf("%d",&n);
	}
	return 0;
}

