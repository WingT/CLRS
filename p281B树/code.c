#include<stdio.h>
#include<stdlib.h>
#define t 2 
typedef struct Bnode{
	int n;
	int leaf;
	char key[t*2-1];
	struct Bnode *c[2*t];
}Bnode;
typedef struct Btree{
	Bnode *root;
}Btree;
int Bcreate(Btree *T)
{
	T->root=(Bnode *)malloc(sizeof(Bnode));
	T->root->n=0;
	T->root->leaf=1;
	return 0;
}
int Bsplitchild(Bnode *x,int i)
{
	Bnode *y,*z;
	y=x->c[i];
	z=(Bnode *)malloc(sizeof(Bnode));
	z->leaf=y->leaf;
	z->n=t-1;
	for (int j=0;j<t-1;j++)
		z->key[j]=y->key[t+j];
	if (!z->leaf)/*尽量不要操作没有初始化的指针,养成良好的习惯还是很重要滴*/
		for (int j=0;j<t;j++)
			z->c[j]=y->c[j+t];
	for (int j=x->n-1;j>=i;j--)
		x->key[j+1]=x->key[j];
	x->key[i]=y->key[t-1];
	for (int j=x->n;j>i;j--)
		x->c[j+1]=x->c[j];
	x->c[i+1]=z;
	x->n++;
	y->n=t-1;
	return 0;
}
int Binsert_nonfull(Bnode *x,char k)
{
	if (x->leaf)
	{
		int i;
		for (i=x->n-1;i>=0 && k<=x->key[i];i--)
			x->key[i+1]=x->key[i];
		i++;
		x->key[i]=k;
		x->n++;
		return 0;
	}
	int i;
	for (i=x->n-1;i>=0 && k<=x->key[i];i--);
	i++;
	if (x->c[i]->n==t*2-1)
	{
		Bsplitchild(x,i);
		if (k>x->key[i])/*这里不要忘了*/
			i++;
	}
	Binsert_nonfull(x->c[i],k);
	return 0;
}
int Binsert(Btree *T,char k)
{
	Bnode *root=T->root;
	if (root->n==t*2-1)
	{
		Bnode *s;
		s=(Bnode *)malloc(sizeof(Bnode));
		s->n=0;
		s->leaf=0;
		s->c[0]=root;
		T->root=s;
		Bsplitchild(s,0);
	}
	Binsert_nonfull(T->root,k);
	return 0;
}
Bnode *Bsearch(Bnode *x,char k,int *i)
{	
	int j;
	int n=x->n;
	for (j=n-1;j>=0 && k<=x->key[j];j--);
	j++;
	if (/*j>=0 && */j<n && k==x->key[j])
	{
		*i=j;
		return x;
	}
	if (x->leaf)
	{
		*i=-1;
		return NULL;
	}
	return Bsearch(x->c[j],k,i);
}
char successor(Bnode *x,int i)/*求内部节点的后继*/
{
	Bnode *tmp;
	for (tmp=x->c[i+1];!tmp->leaf;tmp=tmp->c[0]);
	return tmp->key[0];
}
char predecessor(Bnode *x,int i)/*求内部节点的前驱*/
{
	Bnode *tmp;
	for (tmp=x->c[i];!tmp->leaf;tmp=tmp->c[tmp->n]);
	return tmp->key[tmp->n-1];
}
int Bmerge(Btree *T,Bnode *x,int i)/*合并x.key[i]的左右两个孩子*/
{
	Bnode *y=x->c[i];
	Bnode *z=x->c[i+1];
	y->key[y->n]=x->key[i];
	int j;
	for (j=0;j<t-1;j++)
		y->key[t+j]=z->key[j];
	for (j=0;j<t;j++)
		y->c[t+j]=z->c[j];
	y->n=t*2-1;
	free(z);
	for (j=i;j<x->n-1;j++)
		x->key[j]=x->key[j+1];
	for (j=i+1;j<x->n;j++)
		x->c[j]=x->c[j+1];
	x->n--;
	if (x->n==0)/*一定是内部节点*/
	{
		free(x);
		T->root=y;
	}
	return 0;
}
int Bdelete(Btree *T,Bnode *x,char k)/*疑似有bug,当有重复元素时不知道会不会出错*/
{

	int i;
	for (i=x->n-1;i>=0 && k<=x->key[i];i--);
	i++;
	if (x->leaf)/*情况1*/
	{
		int j;
		for (j=i;j<x->n-1;j++)
			x->key[j]=x->key[j+1];
		x->n--;
		return 0;
	}
	if (i<x->n && x->key[i]==k)
		if (x->c[i]->n>=t)/*情况2a*/
		{
			char k1=predecessor(x,i);
			x->key[i]=k1;
			Bdelete(T,x->c[i],k1);/*如果有重复的元素,也不会出错*/
		}
		else
			if (x->c[i+1]->n>=t)/*情况2b*/
			{
				char k1=successor(x,i);
				x->key[i]=k1;
				Bdelete(T,x->c[i+1],k1);
			}
			else/*情况2c*/
			{
				Bnode *y=x->c[i];
				Bmerge(T,x,i);/*会删除空的非内部空节点*/
				Bdelete(T,y,k);
			}
	else
		if (x->c[i]->n>=t)/*情况3,但是可以直接递归*/
			Bdelete(T,x->c[i],k);
		else
			if (i>0 && x->c[i-1]->n>=t)/*情况3a左*/
			{
				Bnode *y=x->c[i];
				Bnode *z=x->c[i-1];
				int j;
				for (j=y->n-1;j>=0;j--)
					y->key[j+1]=y->key[j];
				for (j=y->n;j>=0;j--)
					y->c[j+1]=y->c[j];
				y->key[0]=x->key[i-1];/*细节啊,害我调试这么久*/
				y->c[0]=z->c[z->n];
				y->n++;
				x->key[i-1]=z->key[z->n-1];/*这里也是!*/
				z->n--;
				Bdelete(T,y,k);
			}
			else
				if (i<x->n && x->c[i+1]->n>=t)/*情况3a右,边界检查别忘了,虽然这里没有出错*/
				{
					Bnode *y=x->c[i];
					Bnode *z=x->c[i+1];
					y->key[y->n]=x->key[i];
					y->c[y->n+1]=z->c[0];
					y->n++;
					x->key[i]=z->key[0];
					int j;
					for (j=0;j<z->n-1;j++)
						z->key[j]=z->key[j+1];
					for (j=0;j<z->n;j++)
						z->c[j]=z->c[j+1];
					z->n--;
					Bdelete(T,y,k);
				}
				else/*情况3b*/
				{
					Bnode *y=x->c[i];
					Bmerge(T,x,i);
					Bdelete(T,y,k);
				}
	return 0;
}
int print(Bnode *x)
{
	int i;
	int n=x->n;
	printf("(");
	for (i=0;i<n-1;i++)
		printf("%c ",x->key[i]);
	if (n)
		printf("%c",x->key[i]);
	printf(")");
	if (x->leaf)
		return 0;
	for (i=0;i<=n;i++)
		print(x->c[i]);
	return 0;
}
int main(void)
{
	Btree T;
	Bcreate(&T);
	int n;
	scanf("%d\n",&n);
	for (int i=0;i<n;i++)
	{
		char k;
		scanf("%c ",&k);
		Binsert(&T,k);
	}
	print(T.root);
	printf("\n");
	scanf("%d\n",&n);
	for (int i=0;i<n;i++)
	{
		char k;
		int j;
		scanf("%c ",&k);
		if (Bsearch(T.root,k,&j))
		{
			printf("%c deleted!:",k);
			Bdelete(&T,T.root,k);
			print(T.root);
			printf("\n");
		}
		else 
			printf("%c:not exist!\n",k);
	}
	printf("\n");
	return 0;
}
