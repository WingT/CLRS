#include<stdio.h>
#include<stdlib.h>
#define white 1
#define gray 2
#define black 3
typedef struct node{
	int d;
	int good;
	int color;
	struct node *next;
}node;
int insert(node *head,node *new)
{
	new->next=head->next;
	head->next=new;
	return 0;
}
typedef struct queue{
	int *q;
	int head,tail,n,size;
}queue;
int enqueue(queue *q,int d)
{
	if (q->n==q->size)
	{
		printf("queue overflow!\n");
		return 0;
	}
	if (q->tail==q->size-1)
		q->tail=0;
	else
		(q->tail)++;	
	q->q[q->tail]=d;
	(q->n)++;
	return 0;
}
int dequeue(queue *q)
{
	int tmp;
	if (q->n==0)
	{
		printf("queue empty!\n");
		return 0;
	}
	tmp=q->q[q->head];
	if (q->head==q->size-1)
		q->head=0;
	else
		(q->head)++;
	q->n--;
	return tmp;
}
int bfs(node *list,int s,queue *q)
{
	int d;
	node *tmp;
	list[s].color=gray;
	enqueue(q,s);
	while (q->n!=0)
	{
		d=dequeue(q);
		tmp=list+d;
		tmp=tmp->next;
		while (tmp!=NULL)
		{
			if (list[tmp->d].color==gray)
			{
				if (list[d].good==list[tmp->d].good)
					return 1;
			}
			else
			{
				enqueue(q,tmp->d);
				list[tmp->d].color=gray;
				list[tmp->d].good=!(list[d].good);
			}
			tmp=tmp->next;
		}
	}
	return 0;
}
int print(node *list,int v)
{
	int i;
	for (i=v;i>=1;i--)
		if (list[i].good==1)
			printf("%d ",i);
	printf("\n");
	for (i=v;i>=1;i--)
		if (list[i].good==0)
			printf("%d ",i);
	printf("\n");
	return 0;
}
int main(void)
{
	int v,e,i,s,d;
	node *list,*new;
	scanf("%d%d",&v,&e);
	list=(node *)malloc(sizeof(node)*(v+1));
	for (i=1;i<=v;i++)
	{
		list[i].next=NULL;
		list[i].color=white;
		list[i].good=0;
	}
	for (i=1;i<=e;i++)
	{
		scanf("%d%d",&s,&d);
		new=(node *)malloc(sizeof(node));
		new->d=d;
		new->next=NULL;
		insert(list+s,new);
		new=(node *)malloc(sizeof(node));
		new->d=s;
		new->next=NULL;
		insert(list+d,new);
	}
	queue q;
	q.q=(int *)malloc(sizeof(int)*(v));
	q.head=0;
	q.tail=v-1;
	q.n=0;
	q.size=v;
	list[1].good=1;
	int ans;
	ans=bfs(list,1,&q);
	switch(ans){
	case 0:printf("ok\n");print(list,v);break;
	case 1:printf("no answer\n");break;
	}
	return 0;
}
