#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define max 30
struct node{
	int n;
	struct node *p,*l,*r;
};
void randomize(int n[],int size)/*将数组元素打乱*/
{
	int i,tmp;
	time_t t;
	srand((unsigned int)time(&t));
	for (i=0;i<size;i++)
		n[i]=i;
	for (i=0;i<size;i++)/*装个逼，下面*几行是交换n[i]和n[tmp]，注意n和tmp相等的时候会出错变成0*/
	{
		tmp=rand()%size;
		if (tmp!=i)
		{
			n[i]=n[i]^n[tmp];
			n[tmp]=n[i]^n[tmp];
			n[i]=n[i]^n[tmp];
		}
	}
}
void insert(struct node **root,int n)/*为什么第一个参数要是二级指针？因为第一次插入的时候树为空，根是NULL，所以根指针会改变*/
{
	struct node *next,*prev,*new;
	next=*root;
	prev=NULL;
	while (next!=NULL)
	{
		prev=next;
		if (n<next->n)
			next=next->l;
		else
			next=next->r;
	}
	new=(struct node *)malloc(sizeof(struct node));
	new->n=n;
	if (prev==NULL)
		*root=new;
	else
	{
		if (n<prev->n)
			prev->l=new;
		else
			prev->r=new;
	}
	new->p=prev;
	new->l=NULL;
	new->r=NULL;
	return;
}
void build(struct node **root,int n[],int size)/*root要是二级指针才行*/
{
	int i;
	*root=NULL;
	for (i=0;i<size;i++)
		insert(root,n[i]);
}
struct node *search(struct node *root,int n)
{
	struct node *next=root;
	while (next!=NULL)
	{
		if (next->n==n)
			return next;
		next=n<next->n?next->l:next->r;
	}
	return NULL;
}
struct node *minmum(struct node *root)
{
	struct node *next=root;
	while (next->l!=NULL)
		next=next->l;
	return next;
}
struct node *maxmum(struct node *root)
{
	struct node *next=root;
	while (next->r!=NULL)
		next=next->r;
	return next;
}
struct node *successor(struct node *root)
{
	struct node *next=root->p,*prev=root;
	if (root->r!=NULL)
		return minmum(root->r);
	else
	{
		while(next!=NULL)
		{
			if (next->l==prev)
				return next;
			prev=next;
			next=next->p;
		}
		return next;
	}
}
struct node *predecessor(struct node *root)
{
	struct node *next=root->p,*prev=root;
	if (root->l!=NULL)
		return maxmum(root->l);
	else
	{
		while(next!=NULL)
		{
			if (next->r==prev)
				return next;
			prev=next;
			next=next->p;
		}
		return next;
	}
}
void transplant(struct node **root,struct node *a,struct node *b)/*b子树移到a子树的位置，参数root的功能是为了修改root*/
{
	if (a->p==NULL)/*注意首先要判断是不是空指针，这里也可以不改变根指针，不过这样的话就得在Delete里加好几行代码*/
		*root=b;
	else
		if (a==a->p->l)
			a->p->l=b;
		else
			a->p->r=b;
	if (b!=NULL)/*也要判断是不是空指针*/
		b->p=a->p;
}
void Delete(struct node **root,struct node *target)/*root有可能改变*/
{
	struct node *tmp;
	if (target==NULL)
		return;
	if (target->l==NULL)
		transplant(root,target,target->r);
	else
		if (target->r==NULL)
			transplant(root,target,target->l);
		else
			if ((tmp=successor(target))==target->r)
			{
				target->l->p=tmp;
				tmp->l=target->l;
				transplant(root,target,tmp);
			}
			else
			{
				transplant(root,tmp,tmp->r);
				tmp->l=target->l;
				tmp->l->p=tmp;
				tmp->r=target->r;
				tmp->r->p=tmp;
				transplant(root,target,tmp);
			}
	free(target);
}
void print(struct node *root)/*以先序遍历方式输出*/
{
	if (root==NULL)
	{
		printf("# ");
		return;
	}
	printf("%d ",root->n);
	print(root->l);
	print(root->r);
}
int main(void)
{
	int n[max];
	randomize(n,max);
	struct node **root,**root2;
	root=(struct node**)malloc(sizeof(struct node *));
	build(root,n,max);
	print(*root);
	printf("\n");
	root2=(struct node**)malloc(sizeof(struct node *));
	build(root2,n,max);
	int a=rand()%max,b=rand()%max;
	Delete(root,search(*root,a));
	Delete(root,search(*root,b));
	print(*root);
	printf("\n");
	Delete(root2,search(*root2,a));
	Delete(root2,search(*root2,b));
	print(*root2);
	return 0;
}
