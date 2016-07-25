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
	int i,d,f,color;
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
typedef struct link_element{
	node *pnode;
	struct link_element *next;
}link_element;
int link_insert(link_element **link,node *pnode)
{
	link_element *new;
	new=(link_element *)malloc(sizeof(link_element));
	new->pnode=pnode;
	new->next=*link;
	*link=new;
	return 0;
}
int sort_visit(gve G,node *pnode,int *time,link_element **link)
{
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	edge *tmp=pnode->next;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
			sort_visit(G,&G.g[tmp->i],time,link);
		tmp=tmp->next;
	}
	(*time)++;
	pnode->f=*time;
	pnode->color=black;
	link_insert(link,pnode);
	return 0;
}
link_element *topological_sort(gve G)
{
	int i,time=0;
	link_element **link;
	link=(link_element **)malloc(sizeof(link_element *));
	*link=NULL;
	for (i=1;i<=G.v;i++)
		if (G.g[i].color==white)
			sort_visit(G,&G.g[i],&time,link);
	return *link;
}
int print(link_element *link)
{
	link_element *tmp=link;
	while (tmp!=NULL)
	{
		printf("%d ",tmp->pnode->i);
		tmp=tmp->next;
	}
	printf("\n");
	return 0;
}
int main(void)
{
	gve G;
	int i;
	scanf("%d%d",&G.v,&G.e);
	G.g=(node *)malloc(sizeof(node)*(G.v+1));
	for (i=1;i<=G.v;i++)
	{
		G.g[i].i=i;
		G.g[i].color=white;
		G.g[i].next=NULL;
	}
	int s,d;
	for (i=1;i<=G.e;i++)
	{
		scanf("%d%d",&s,&d);
		insert(&G.g[s],d);
	}
	link_element *ans;
	ans=topological_sort(G);
	print(ans);
}
