#define debug 0
#include<stdio.h>
#include<stdlib.h>
#define white 1
#define gray 2
#define black 3
typedef struct edge{
	int i;
	struct edge *next;
}edge;
typedef struct node{
	int d,f,color;
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
//int dfsvisit(gve G,node *pnode,int *time)
//{
//	edge *tmp=pnode->next;
//	(*time)++;
//	pnode->d=*time;
//	pnode->color=gray;
//	while (tmp!=NULL)
//	{
//		if (G.g[tmp->i].color==white)
//			dfsvisit(G,&G.g[tmp->i],time);
//		tmp=tmp->next;
//	}
//	pnode->color=black;
//	(*time)++;
//	pnode->f=*time;
//	return 0;
//}
typedef struct stack_element{
	node *pnode;
	edge *tmp;
}stack_element;
typedef struct stack{
	int size,tail;
	stack_element *head;
}stack;
int push(stack *visit_stack,node *pnode,edge *tmp)
{
	if (visit_stack->tail==visit_stack->size-1)
	{
		printf("stack overflow!\n");
		return 0;
	}
	visit_stack->tail++;
	visit_stack->head[visit_stack->tail].pnode=pnode;
	visit_stack->head[visit_stack->tail].tmp=tmp;
	return 0;
}
int pop(stack *visit_stack)
{
	visit_stack->tail--;
	return 0;
}
int dfsvisit(gve G,node *pnode,int *time)
{
	stack visit_stack;
	visit_stack.size=G.v;
	visit_stack.tail=-1;
	visit_stack.head=(stack_element *)malloc(sizeof(stack_element)*(G.v));
	edge *tmp=pnode->next;
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	push(&visit_stack,pnode,tmp);
	while (visit_stack.tail!=-1)
	{
		tmp=visit_stack.head[visit_stack.tail].tmp;
		while ((tmp!=NULL)&&(G.g[tmp->i].color!=white))
			tmp=tmp->next;
		if (tmp==NULL)
		{
			pnode=visit_stack.head[visit_stack.tail].pnode;
			pnode->color=black;
			(*time)++;
			pnode->f=*time;
			pop(&visit_stack);
		}
		else
		{
			visit_stack.head[visit_stack.tail].tmp=tmp;
			push(&visit_stack,&G.g[tmp->i],G.g[tmp->i].next);
			(*time)++;
			visit_stack.head[visit_stack.tail].pnode->d=*time;
			visit_stack.head[visit_stack.tail].pnode->color=gray;
		}
	}
	free(visit_stack.head);
	return 0;
}
int dfs(gve G)
{
	int time=0,i;
	for (i=1;i<=G.v;i++)
		if (G.g[i].color==white)
			dfsvisit(G,&G.g[i],&time);
	return 0;
}
int printtree(gve G)
{
	int i;
	for (i=1;i<=G.v;i++)
		printf("%d: color %d d %d f %d\n",i,G.g[i].color,G.g[i].d,G.g[i].f);
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
		G.g[i].color=white;
	}
	int s,d;
	for (i=1;i<=G.e;i++)
	{
		scanf("%d%d",&s,&d);
		insert(&G.g[s],d);
	}
	dfs(G);
	printtree(G);
	return 0;
}
