#define white 1
#define gray 2
#define black 3
#include<stdio.h>
#include<stdlib.h>
typedef struct edge{
	int i;
	struct edge *next;
}edge;
typedef struct node{
	int i,d,f,color,cc;
	edge *next;
}node;
typedef struct gve{
	int v,e;
	node *g;
}gve;
int insert(node *pnode,int d)
{
	edge *new;
	new=(edge *)malloc(sizeof(edge));
	new->i=d;
	new->next=pnode->next;
	pnode->next=new;
	return 0;
}
typedef struct link_element{
	int i;
	struct link_element *next;
}link_element;
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
	edge *tmp;
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	tmp=pnode->next;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
			dfsvisit(G,&G.g[tmp->i],time,link);
		tmp=tmp->next;
	}
	(*time)++;
	pnode->f=*time;
	pnode->color=black;
	link_insert(link,pnode->i);
	return 0;
}
int dfs(gve G,link_element **link)
{
	int i,time=0;
	for (i=1;i<=G.v;i++)
		if (G.g[i].color==white)
			dfsvisit(G,&G.g[i],&time,link);
	return 0;
}
gve trans(gve G)
{
	gve Gt;
	int i;
	Gt.v=G.v;
	Gt.e=G.e;
	Gt.g=(node *)malloc(sizeof(node)*(G.v+1));
	for (i=1;i<=Gt.v;i++)
	{
		Gt.g[i].color=white;
		Gt.g[i].i=i;
		Gt.g[i].next=NULL;
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
int dfsvisit2(gve G,node *pnode,int *time,int cc)
{
	edge *tmp;
	(*time)++;
	pnode->d=*time;
	pnode->color=gray;
	tmp=pnode->next;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
			dfsvisit2(G,&G.g[tmp->i],time,cc);
		tmp=tmp->next;
	}
	(*time)++;
	pnode->f=*time;
	pnode->color=black;
	pnode->cc=cc;
	printf("%d ",pnode->i);
	return 0;
}
int dfs2(gve G,link_element *link)
{
	int time=0,cc=1;
	link_element *tmp=link;
	while (tmp!=NULL)
	{
		if (G.g[tmp->i].color==white)
		{
			dfsvisit2(G,&G.g[tmp->i],&time,cc);
			printf(":%d\n",G.g[tmp->i].cc);
			cc++;
		}
		tmp=tmp->next;
	}
	return cc-1;
}
int print(gve G)
{
	int i;
	edge *tmp;
	for (i=1;i<=G.v;i++)
	{
		printf("%d: ",G.g[i].i);
		tmp=G.g[i].next;
		while (tmp!=NULL)
		{
			printf("%d ",tmp->i);
			tmp=tmp->next;
		}
		printf("\n");
	}
	return 0;
}
typedef struct tmp_edge{
	int x,y;
}tmp_edge;
int radix_sort(tmp_edge *tmpedge,int count)
{
	int *x,*y;
	x=(int *)malloc(sizeof(int)*(count+1));
	y=(int *)malloc(sizeof(int)*(count+1));
	int i;
	for (i=1;i<=count;i++)
	{
		x[i]=tmpedge[i].x;
		y[i]=tmpedge[i].y;
	}
	stable_sort(tmpedge,)
}
gve scc(gve G)
{
	link_element **link;
	link=(link_element **)malloc(sizeof(link_element *));
	*link=NULL;
	dfs(G,link);
	gve Gt;
	Gt=trans(G);
	int cc;
	cc=dfs2(Gt,*link);
	int i;
	for (i=1;i<=G.v;i++)
		G.g[i].cc=Gt.g[i].cc;
	gve Gscc;
	Gscc.v=cc;
	Gscc.g=(node *)malloc(sizeof(node)*(cc+1));
	for (i=1;i<=cc;i++)
	{
		Gscc.g[i].i=i;
		Gscc.g[i].next=NULL;
	}
	tmp_edge *tmpedge;
	tmpedge=(tmp_edge *)malloc(sizeof(tmp_edge)*(G.e+1));
	edge *tmp;
	int count=1;
	for (i=1;i<=G.v;i++)
	{
		tmp=G.g[i].next;
		while (tmp!=NULL)
		{
			if (G.g[i].cc!=G.g[tmp->i].cc)
			{
				tmpedge[count].x=G.g[i].cc;
				tmpedge[count].y=G.g[tmp->i].cc;
				count++;
			}
		}
	}
	count--;
	radix_sort(tmpedge,count);
	tmpedge[0].x=0;
	tmpedge[0].y=0;
	for (i=1;i<=count;i++)
		if (!((tmpedge[i].x==tmpedge[i-1].x)&&(tmpedge[i].y==tmpedge[i-1].y)))
			insert(&Gscc.g[tmpedge[i].x],tmpedge[i].y);
	return Gscc;
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
	scc(G);
	printf("\n");
	return 0;
}
