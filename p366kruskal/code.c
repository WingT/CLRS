#include<stdio.h>
#include<stdlib.h>
typedef struct edve{
	int u,v,w;
}edge;
typedef struct node{
	int rank;
	struct node *p;
}node;
typedef struct gve{
	int vn,en;
	node *v;
	edge *e;
}gve;
int swap(edge *e,int a,int b)
{
	edge tmp;
	tmp=e[a];
	e[a]=e[b];
	e[b]=tmp;
	return 0;
}
int partition(edge *e,int l,int r)
{
	int i,k=l-1;
	for (i=l;i<r;i++)
		if (e[i].w<=e[r].w)
			swap(e,++k,i);
	swap(e,++k,r);
	return k;
}
int Qsort(edge *e,int l,int r)
{
	if (l>=r)
		return 0;
	int k;
	k=partition(e,l,r);
	Qsort(e,l,k-1);
	Qsort(e,k+1,r);
	return 0;
}
int init(gve *G)
{
	int n,m,i;
	scanf("%d%d",&n,&m);
	G->vn=n;
	G->v=(node *)malloc(sizeof(node)*(n+1));
	G->en=m;
	G->e=(edge *)malloc(sizeof(edge)*(m+1));
	for (i=1;i<=n;i++)//make-set
	{
		G->v[i].rank=0;
		G->v[i].p=G->v+i;
	}
	int u,v,w;
	for (i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		G->e[i].u=u;
		G->e[i].v=v;
		G->e[i].w=w;
	}
	Qsort(G->e,1,m);
	return 0;
}
//int print(gve G)
//{
//	int i;
//	printf("v:%d e:%d\n",G.vn,G.en);
//	for (i=1;i<=G.en;i++)
//		printf("%d<-->%d:%d\n",G.e[i].u,G.e[i].v,G.e[i].w);
//	return 0;
//}
node *findset(node *x)
{
	if (x==x->p)
		return x;
	x->p=findset(x->p);
	return x->p;
}
int Union(node *x,node *y)
{
	node *fx,*fy;
	fx=findset(x);
	fy=findset(y);
	if (fx->rank>fy->rank)
		fy->p=fx;
	else
	{
		fx->p=fy;
		if (fx->rank==fy->rank)
			fy->rank++;
	}
	return 0;
}
int kruskal(gve G)
{
	int i,ans=0;
	for (i=1;i<=G.en;i++)
		if (findset(G.v+G.e[i].u)!=findset(G.v+G.e[i].v))
		{
			Union(G.v+G.e[i].u,G.v+G.e[i].v);
			ans+=G.e[i].w;
		}
	return ans;
}
int main(void)
{
	gve G;
	init(&G);
	int ans;
	ans=kruskal(G);
	printf("%d",ans);
	return 0;
}
