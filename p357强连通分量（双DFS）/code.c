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
typedef struct link_element{
	int i;
	struct link_element *next;
}link_element;
int insert(node *pnode,int i)
{
	edge *new;
	new=(edge *)malloc(sizeof(edge));
	new->i=i;
	new->next=pnode->next;
	pnode->next=new;
	return 0;
}
int link_insert(link_element **link,int i)
{
	link_element *new;
	new=(link_element *)malloc(sizeof(link_element));
	new->i=i;
	new->next=*link;
	*link=new;
	return 0;
}
int dfsvisit(gve G,node *pnode,int *time,link_element **link)
{
	edge *tmp=pnode->next;
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
			dfsvisit(G,&G.g[tmp->i],time,link);
		tmp=tmp->next;
	}
	pnode->color=black;
	(*time)++;
	pnode->f=*time;
	link_insert(link,pnode->i);
	return 0;
}
int dfs(gve G,link_element **link)
{
	int time=0,i;
	for (i=1;i<=G.v;i++)
		if (G.g[i].color==white)
			dfsvisit(G,&G.g[i],&time,link);
	return 0;
}
int dfsvisit2(gve G,node *pnode,int *time)
{
	edge *tmp=pnode->next;
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	printf("%d ",pnode->i);
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
			dfsvisit2(G,&G.g[tmp->i],time);
		tmp=tmp->next;
	}
	pnode->color=black;
	(*time)++;
	pnode->f=*time;
	return 0;
}
int dfs2(gve G,link_element **link)
{
	int time=0;
	link_element *tmp=*link;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
		{
			dfsvisit2(G,&G.g[tmp->i],&time);
			printf("\n");
		}
		tmp=tmp->next;
	}
	return 0;
}
gve trans(gve G)
{
	gve Gt;
	Gt.v=G.v;
	Gt.e=G.e;
	Gt.g=(node *)malloc(sizeof(node)*(Gt.v+1));
	int i;
	for (i=1;i<=Gt.v;i++)
	{
		Gt.g[i].next=NULL;
		Gt.g[i].color=white;
		Gt.g[i].i=i;
	}
	edge *tmp;
	for (i=1;i<=Gt.v;i++)
	{
		tmp=G.g[i].next;
		while (tmp!=NULL)
		{
			insert(&Gt.g[tmp->i],i);
			tmp=tmp->next;
		}
	}
	return Gt;
}
int css(gve G)
{
	link_element **link;
	link=(link_element **)malloc(sizeof(link_element *));
	*link=NULL;
	gve Gt;
	dfs(G,link);
	Gt=trans(G);
	dfs2(Gt,link);
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
		G.g[i].i=i;
	}
	int s,d;
	for (i=1;i<=G.e;i++)
	{
		scanf("%d%d",&s,&d);
		insert(&G.g[s],d);
	}
	css(G);
	return 0;
}
