#include<stdio.h>
#include<stdlib.h>
#define white 1
#define gray 2
#define black 3
typedef struct set_element set_element;
typedef struct set_link_element{
	int i;
	struct set_link_element *next;
	set_element *set;
}set_link_element;
struct set_element{
	int size;
	set_link_element *head,*tail;
};
typedef struct edge{
	int i;
	struct edge *next;
}edge;
typedef struct node{
	int d,f,color;
	edge *next;
	set_link_element *self;
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
set_link_element *makeset(set_element *set,int i)
{
	set_link_element *New;
	New=(set_link_element *)malloc(sizeof(set_link_element));
	New->next=NULL;
	New->i=i;
	New->set=set+i;
	set[i].head=New;
	set[i].tail=New;
	set[i].size=1;
	return New;
}
set_element *findset(set_link_element *pnode)
{
	return pnode->set;
}
int Union(set_link_element *a,set_link_element *b)
{
	if (a->set->size>b->set->size)
	{
		set_link_element *tmp=b->set->head;
		while (tmp!=NULL)
		{
			tmp->set=a->set;
			tmp=tmp->next;
		}
		(a->set->tail)->next=b->set->head;
		a->set->tail=b->set->tail;
	}
	else
	{
		set_link_element *tmp=a->set->head;
		while (tmp!=NULL)
		{
			tmp->set=b->set;
			tmp=tmp->next;
		}
		(b->set->tail)->next=a->set->head;
		b->set->tail=a->set->tail;
	}
	return 0;
}
int main(void)
{
	int i;
	gve G;
	scanf("%d%d",&G.v,&G.e);
	G.g=(node *)malloc(sizeof(node)*(G.v+1));
	set_element *set;
	set=(set_element *)malloc(sizeof(set_element)*(G.v+1));
	for (i=1;i<=G.v;i++)
	{
		G.g[i].next=NULL;
		G.g[i].color=white;
		G.g[i].self=makeset(set,i);
	}
	int s,d;
	for (i=1;i<=G.e;i++)
	{
		scanf("%d%d",&s,&d);
		insert(&G.g[s],d);
		if (findset(G.g[s].self)!=findset(G.g[d].self))
			Union(G.g[s].self,G.g[d].self);
	}
}
