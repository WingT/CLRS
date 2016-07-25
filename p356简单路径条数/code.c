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
	int d,f,color,count;
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
int dfsvisit(gve G,node *pnode,int *time)
{
	edge *tmp=pnode->next;
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
			dfsvisit(G,&G.g[tmp->i],time);
		pnode->count+=G.g[tmp->i].count;
		tmp=tmp->next;
	}
	pnode->color=black;
	(*time)++;
	pnode->f=*time;
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
		G.g[i].count=0;
		G.g[i].next=NULL;
		G.g[i].color=white;
	}
	int s,d;
	for (i=1;i<=G.e;i++)
	{
		scanf("%d%d",&s,&d);
		insert(&G.g[s],d);
	}
	scanf("%d%d",&s,&d);
	G.g[d].count=1;
	int time=0;
	dfsvisit(G,&G.g[s],&time);
	printf("%d\n",G.g[s].count);
	return 0;
}
