#include<stdio.h>
#include<stdlib.h>
struct node{
	int f;
	struct node *l,*r;
};
struct heap{
	int f;
	struct node *hnode;
};
int minheapify(struct heap *q,int i,int heapsize)
{
	int min;
	struct heap tmp;
	tmp=q[i];
	while (1)
	{
		min=i;
		if (i*2<=heapsize)
			min=tmp.f<q[i*2].f?i:i*2;
		if (i*2+1<=heapsize)
			min=q[min].f<q[i*2+1].f?min:i*2+1;
		if (min!=i)
		{
			q[i]=q[min];
			i=min;
		}
		else
			break;
	}
	q[min]=tmp;
	return 0;
}
int buildminheap(struct heap*q,int heapsize)
{
	int i;
	for (i=heapsize/2;i>=1;i--)
		minheapify(q,i,heapsize);
	return 0;
}
struct node * extractmin(struct heap *q,int heapsize)
{
	struct heap tmp;
	tmp=q[1];
	q[1]=q[heapsize];
	minheapify(q,1,heapsize-1);
	return tmp.hnode;
}
int insert(struct heap *q,struct node *new,int heapsize)
{
	struct heap tmp;
	int min,i;
	heapsize++;
	q[heapsize].f=new->f;
	q[heapsize].hnode=new;
	tmp=q[heapsize];
	i=heapsize;
	while (1)
	{
		min=i;
		if ((i>1)&&(q[i/2].f>tmp.f))
			min=i/2;
		if (min!=i)
		{
			q[i]=q[min];
			i=min;
		}
		else
			break;
	}
	q[min]=tmp;
	return 0;
}
struct node * huffman(struct heap *q,int n)
{
	int i;
	struct node *new;
	for (i=n;i>1;i--)//heapsize
	{
		new=(struct node *)malloc(sizeof(struct node));
		new->l=extractmin(q,i);
		new->r=extractmin(q,i-1);
		new->f=new->l->f+new->r->f;
		insert(q,new,i-2);
	}
	return new;
}
int print(struct node *root)
{
	if (root==NULL)
	{
		printf("# ");
		return 0;
	}
	printf("%d ",root->f);
	print(root->l);
	print(root->r);
	return 0;
}
int main(void)
{
	int n,i;
	struct heap* q;
	scanf("%d",&n);
	q=(struct heap *)malloc(sizeof(struct heap)*(n+1));
	for (i=1;i<=n;i++)
	{
		q[i].hnode=(struct node *)malloc(sizeof(struct node));
		q[i].hnode->l=NULL;
		q[i].hnode->r=NULL;
		scanf("%d",&q[i].f);
		q[i].hnode->f=q[i].f;
	}
	buildminheap(q,n);
	struct node *hroot;
	hroot=huffman(q,n);
	print(hroot);
	printf("\n");
	return 0;
}
