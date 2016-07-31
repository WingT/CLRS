/*
 * source.c
 *
 *  Created on: Mar 3, 2016
 *      Author: wing
 */
#include<stdio.h>
#include<stdlib.h>
#define MAX 6
#define black 1
#define red 0
struct node{
	int n;
	int color,high,low,max;
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
		printf("#(%d) ",root->color);
		return 0;
	}
	else
	{
		printf("%d(%d) ",root->n,root->color);
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
		}
	if (yoc==black)/*删除（移动）黑色的y节点只会对以x为根的子树的黑节点数产生影响*/
		rbdeletefixup(t,x);
	return 0;
}
int main(void)
{
	struct tree *t;
	t=(struct tree *)malloc(sizeof(struct tree));
	t->nil=(struct node *)malloc(sizeof(struct node));
	t->nil->color=black;
	t->root=t->nil;
	struct node *new;
	int i,x[10]={0,5,6},y[6]={8,12,19,31,38,41};
	for (i=0;i<MAX;i++)
	{
		new=(struct node *)malloc(sizeof(struct node));
		new->n=x[i];
		new->color=red;
		rbinsert(t,new);
	}
	print(t,t->root);
	printf("\n");
	for (i=0;i<MAX;i++)
	{
		rbdelete(t,search(t,t->root,y[i]));
		print(t,t->root);
		printf("\n");
	}
	return 0;
}

