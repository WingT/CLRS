/*
 * source.c
 *
 *  Created on: Mar 3, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define max 6
#define black 1
#define red 0
int count=0;
struct node{
	int n;
	int color,size;
	struct node *p,*l,*r;
};
struct tree{
	struct node *root,*nil;
};
int leftrotate(struct tree *t,struct node *x)
{
	struct node *y;
	y=x->r;
	x->r=y->l;
	if (y->l!=t->nil)
		y->l->p=x;
	/*x->p=y;千万千万注意顺序啊!*/
	y->l=x;
	y->p=x->p;
	if (x==t->root)
		t->root=y;
	else
		if (x==x->p->l)
			x->p->l=y;
		else
			x->p->r=y;
	x->p=y;
	y->size=x->size;/**/
	x->size=x->l->size+x->r->size+1;/*旋转会改变size属性，着色不会*/
	return 0;
}
int rightrotate(struct tree *t,struct node *x)
{
	struct node *y;
	y=x->l;
	x->l=y->r;
	if (y->r!=t->nil)
		y->r->p=x;
	/*x->p=y;*/
	y->r=x;
	y->p=x->p;
	if (x==t->root)
		t->root=y;
	else
		if (x==x->p->l)
			x->p->l=y;
		else
			x->p->r=y;
	x->p=y;
	y->size=x->size;/**/
	x->size=x->l->size+x->r->size+1;/*修改size属性*/
	return 0;
}
int rbinsertfixup(struct tree *t,struct node *x)
{
	while (x->p->color==red)
		if (x->p==x->p->p->l)
			if (x->p->p->r->color==red)
			{
				x=x->p->p;
				x->color=red;
				x->l->color=black;
				x->r->color=black;
			}/*case1,只有这种情况循环才会继续*/
			else
			{
				if (x==x->p->r)
				{
					x=x->p;
					leftrotate(t,x);
				}/*case2*/
				x->p->color=black;
				x->p->p->color=red;
				rightrotate(t,x->p->p);/*case3*/
			}
		else
			if (x->p->p->l->color==red)
			{
				x=x->p->p;
				x->color=red;
				x->l->color=black;
				x->r->color=black;
			}
			else
			{
				if (x==x->p->l)
				{
					x=x->p;
					rightrotate(t,x);
				}
				x->p->color=black;
				x->p->p->color=red;
				leftrotate(t,x->p->p);
			}
	t->root->color=black;
	return 0;
}
int rbinsert(struct tree *t,struct node *new)
{
	struct node *next=t->root,*prev=t->nil;
	while (next!=t->nil)
	{
		prev=next;
		next=new->n<next->n?next->l:next->r;
		count=new->n<prev->n?count+prev->size-next->size:count;
		(prev->size)++;/*插入时经过节点size+1，不需要考虑新增节点是根节点的情况*/
	}
	new->p=prev;
	new->l=t->nil;
	new->r=t->nil;
	if (t->root==t->nil)
		t->root=new;
	else
		if (new->n<prev->n)
			prev->l=new;
		else
			prev->r=new;/*和二叉搜索树几乎是一样的，区别只在于NULL换成了t.nil*/
	rbinsertfixup(t,new);
	return 0;
}
struct node *search(struct tree *t,struct node *root,int key)
{
	if (root==t->nil||root->n==key)
		return root;
	else
		if (key<root->n)
			return search(t,root->l,key);
		else
			return search(t,root->r,key);
}
int print(struct tree *t,struct node *root)
{
	if (root==t->nil)
	{
		printf("#/%d(%d) ",root->size,root->color);
		return 0;
	}
	else
	{
		printf("%d/%d(%d) ",root->n,root->size,root->color);
		print(t,root->l);
		print(t,root->r);
		return 0;
	}
}
int rbtransplant(struct tree *t,struct node *u,struct node *v)
{
	if (u==t->root)
		t->root=v;
	else
		if (u==u->p->l)
			u->p->l=v;
		else
			u->p->r=v;
	v->p=u->p;/*注意即使u是t.nil也要赋值，便于fixup*/
	return 0;
}
struct node *rbminnum(struct tree *t,struct node *root)
{
	struct node *next=root;
	while (next->l!=t->nil)
		next=next->l;
	return next;
}
int rbdeletefixup(struct tree *t,struct node *x)
{
	struct node*w;
	while (x!=t->root&&x->color==black)
		if (x==x->p->l)
		{
			w=x->p->r;
			if (w->color==red)
			{
				w->color=black;
				w->p->color=red;
				w=w->l;
				leftrotate(t,x->p);
			}/*case1*/
			if (w->l->color==black&&w->r->color==black)
			{
				w->color=red;
				x=x->p;
			}/*case2，只有这种情况循环才会继续*/
			else
			{
				if (w->r->color==black)/*书上的代码非常精炼，没有一点多余，之前还判断了w.l.color是不是red*/
				{
					w->l->color=black;
					w->color=red;
					rightrotate(t,w);
					w=x->p->r;
				}/*case3*/
				w->color=x->p->color;
				x->p->color=black;
				w->r->color=black;
				leftrotate(t,x->p);
				x=t->root;/*case4*/
			}
		}
		else
		{
			w=x->p->l;
			if (w->color==red)
			{
				w->color=black;
				w->p->color=red;
				w=w->r;
				rightrotate(t,x->p);
			}
			if (w->l->color==black&&w->r->color==black)
			{
				w->color=red;
				x=x->p;
			}
			else
			{
				if (w->l->color==black)
				{
					w->r->color=black;
					w->color=red;
					leftrotate(t,w);
					w=x->p->l;
				}
				w->color=x->p->color;
				x->p->color=black;
				w->l->color=black;
				rightrotate(t,x->p);
				x=t->root;
			}
		}
	x->color=black;/*如果x是根节点，性质2会被破坏，在这里修复*/
	return 0;
}
int rbdelete(struct tree *t,struct node *z)
{
	struct node *x,*y;
	int yoc;/*y_original_color*/
	if (z==t->nil)
		return 0;
	y=z;
	yoc=z->color;/*y是删除的节点*/
	if (y->l==t->nil)
	{
		x=y->r;
		rbtransplant(t,y,x);/*x可能为t.nil*/
	}
	else
		if (y->r==t->nil)
		{
			x=y->l;
			rbtransplant(t,y,x);
		}
		else
		{
			y=rbminnum(t,z->r);
			yoc=y->color;/*y是移向内部的节点*/
			x=y->r;
			if (y->p==z)
				x->p=y;/*因为没有rbtransplant(t,y,x),也就没有对x.p进行赋值，这是如果x是t.nil，进行fixup是就会出错*/
			else
			{
				rbtransplant(t,y,x);
				y->r=z->r;
				y->r->p=y;
			}
			rbtransplant(t,z,y);
			y->l=z->l;
			y->l->p=y;
			y->color=z->color;
			y->size=z->size;/*由于使用y替换z，因此y的size属性要改成z的，别急，下面会修复这条路径上所有节点的size属性*/
		}
	struct node *p=x->p;
	while (p!=t->nil)
	{
		(p->size)--;
		p=p->p;
	}/*这个循环修复待删除节点所在路径上节点的size属性*/
	if (yoc==black)/*删除（移动）黑色的y节点只会对以x为根的子树的黑节点数产生影响*/
		rbdeletefixup(t,x);
	free(z);
	return 0;
}
struct node *osselect(struct tree *t,int i)/*根据秩返回节点指针*/
{
	struct node *next=t->root;
	if (i<=0||i>t->root->size)
		return t->nil;
	int r=next->l->size+1;
	while (r!=i)
	{
		if (i<r)
			next=next->l;
		else
		{
			next=next->r;
			i-=r;
		}
		r=next->l->size+1;
	}
	return next;
}
int osrank(struct tree *t,struct node *x)/*返回节点的秩*/
{
	struct node *next=x;
	int r=next->l->size+1;
	while (next!=t->root)
	{
		if (next==next->p->r)
			r+=next->p->l->size+1;
		next=next->p;
	}
	return r;
}
int main(void)
{
	struct tree *t;
	t=(struct tree *)malloc(sizeof(struct tree));
	t->nil=(struct node *)malloc(sizeof(struct node));
	t->nil->color=black;
	t->nil->size=0;/*空节点的size设为0，保证正确性*/
	t->root=t->nil;
	struct node *new;
	int i,x[6]={41,38,31,12,19,8};
	for (i=0;i<max;i++)
	{
		new=(struct node *)malloc(sizeof(struct node));
		new->n=x[i];
		new->color=red;
		new->size=1;/*新添节点size设为1*/
		rbinsert(t,new);
	}
	printf("%d",count);
	return 0;
}



