/*
 * stack.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
/*
 * stack.c
 *
 *  Created on: Feb 22, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 10
struct stack{
	int s[max];
	int head;
	int tail;
};
int pop(struct stack *S)
{
	if (S->tail==-1)
	{
		printf("Stack underflow!\n");
		return 0;
	}
	else
	{
		printf("%d\n",S->s[S->tail]);
		(S->tail)--;
		return 0;
	}
}
int push(struct stack *S)
{
	int tmp;
	if (S->tail==max-1)
	{
		printf("Stack overflow!\n");
		return 0;
	}
	else
	{
		scanf("%d",&tmp);
		(S->tail)++;
		S->s[S->tail]=tmp;
		return 0;
	}
}
int main(void)
{
	int n;
	struct stack *S;
	S=(struct stack *)malloc(sizeof(struct stack));
	S->head=0;
	S->tail=-1;
	scanf("%d",&n);
	while (n!=-1)
	{
		switch(n)
		{
		case 0:pop(S);break;
		case 1:push(S);break;
		default:break;
		}
		scanf("%d",&n);
	}
	return 0;
}



