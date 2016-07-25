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
#if debug
int print(gve G)
{
	int i;
	edge *tmp;
	printf("This is for debug!\n");
	printf("%d %d\n",G.v,G.e);
	for (i=1;i<=G.v;i++)
	{
		printf ("%d: ",i);
		tmp=G.g[i].next;
		while (tmp!=NULL)
		{
			printf("%d ",tmp->i);
			tmp=tmp->next;
		}
		printf("\n");
	}
	printf("end!\n");
	return 0;
}
#endif
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
		tmp=tmp->next;
	}
	pnode->color=black;
	(*time)++;
	pnode->f=*time;
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
	#if debug 
		print(G);
	#endif
	dfs(G);
	printtree(G);
	return 0;
}
