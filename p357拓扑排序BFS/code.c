#include<stdio.h>
#include<stdlib.h>
typedef struct edge{
	int i;
	struct edge *next;
}edge;
typedef struct node{
	int i,in;
	edge *next;
}node;
typedef struct gve{
	int v,e;
	node *g;
}gve;
int insert(node *pnode,int i)
{
	edge *new;
	new=(edge *)malloc(sizeof(edge));
	new->i=i;
	new->next=pnode->next;
	pnode->next=new;
	return 0;
}
typedef struct queue{
	int head,tail,size,n;
	node **que;
}queue;
int enqueue(queue *q,node *pnode)
{
	if (q->n==q->size)
	{
		printf("queue overflow!\n");
		return 0;
	}
	q->tail=q->tail==q->size-1?0:q->tail+1;
	q->que[q->tail]=pnode;
	q->n++;
	return 0;
}
int dequeue(queue *q)
{
	if (q->n==0)
	{
		printf("queue empty!\n");
		return 0;
	}
	q->head=q->head==q->size-1?0:q->head+1;
	q->n--;
	return 0;
}
int topological_sort(gve *G)
{
	queue q;
	q.head=0;
	q.tail=-1;
	q.size=G->v;
	q.n=0;
	q.que=(node **)malloc(sizeof(node*)*(q.size));
	int i;
	for (i=1;i<=G->v;i++)
		if (G->g[i].in==0)
			enqueue(&q,&(G->g[i]));
	edge *tmp;
	while (q.n!=0)
	{
		tmp=q.que[q.head]->next;
		while (tmp!=NULL)
		{
			G->g[tmp->i].in--;
			if (G->g[tmp->i].in==0)
				enqueue(&q,&(G->g[tmp->i]));
			tmp=tmp->next;
		}
		printf("%d ",q.que[q.head]->i);
		dequeue(&q);
	}
	return 0;
}
int main(void)
{
	int i;
	gve G;
	scanf("%d%d",&G.v,&G.e);
	G.g=(node *)malloc(sizeof(node)*(G.v+1));
	for (i=1;i<=G.v;i++)
	{
		G.g[i].next=NULL;
		G.g[i].in=0;
		G.g[i].i=i;
	}
	int s,d;
	for (i=1;i<=G.e;i++)
	{
		scanf("%d%d",&s,&d);
		insert(&G.g[s],d);
		G.g[d].in++;
	}
	topological_sort(&G);
	printf("\n");
	return 0;
}
