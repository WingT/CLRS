/*attention if max set to 1000 will cause segmentation fault*/
#include<stdio.h>
#include<stdlib.h>
#define max 100
#define inf 1e20
struct node{
	int n;
	struct node *l,*r;
};
float optimal_bst(float p[],float q[],float e[][max+1],int root[][max+1],int n)
{
	int i,j,r,l;
	float w[max+2][max+1];
	for (i=1;i<=n+1;i++)
	{
		e[i][i-1]=q[i-1];
		w[i][i-1]=q[i-1];
	}
	for (l=0;l<=n-1;l++)
		for (i=1;i<=n-l;i++)
		{
			j=i+l;
			w[i][j]=w[i][j-1]+p[j]+q[j];
			e[i][j]=inf;
			for (r=i;r<=j;r++)
				if (e[i][r-1]+e[r+1][j]+w[i][j]<e[i][j])
				{
					e[i][j]=e[i][r-1]+e[r+1][j]+w[i][j];
					root[i][j]=r;
				}
		}
	return e[1][n];
}
float optimal_bst2(float p[],float q[],float e[][max+1],int root[][max+1],int n)
{
	int i,j,r,l;
	float w[max+2][max+1];
	for (i=1;i<=n+1;i++)
	{
		e[i][i-1]=q[i-1];
		w[i][i-1]=q[i-1];
	}
	for (i=1;i<=n;i++)
	{
		root[i][i]=i;
		w[i][i]=w[i][i-1]+p[i]+q[i];
		e[i][i]=e[i][i-1]+e[i+1][i]+w[i][i];
	}
	for (l=1;l<=n-1;l++)
		for (i=1;i<=n-l;i++)
		{
			j=i+l;
			w[i][j]=w[i][j-1]+p[j]+q[j];
			e[i][j]=inf;
			for (r=root[i][j-1];r<=root[i+1][j];r++)
				if (e[i][r-1]+e[r+1][j]+w[i][j]<e[i][j])
				{
					e[i][j]=e[i][r-1]+e[r+1][j]+w[i][j];
					root[i][j]=r;
				}
		}
	return e[1][n];
}
int construct_optimal_bst(int root[][max+1],struct node *troot,int l,int r)
{
	struct node *new;
	int tmp;
	new=(struct node *)malloc(sizeof(struct node));
	if (l>r)
	{
		troot->n=r;
		troot->l=NULL;
		troot->r=NULL;
		return 0;
	}
	tmp=root[l][r];
	troot->n=tmp;
	troot->l=(struct node *)malloc(sizeof(struct node));
	troot->r=(struct node *)malloc(sizeof(struct node));
	construct_optimal_bst(root,troot->l,l,tmp-1);
	construct_optimal_bst(root,troot->r,tmp+1,r);
	return 0;
}
int print(struct node *troot)
{
	if (troot==NULL)
	{
		printf("# ");
		return 0;
	}
	if ((troot->l==NULL)&&(troot->r==NULL))
		printf("d%d ",troot->n);
	else
		printf("k%d ",troot->n);
	print(troot->l);
	print(troot->r);
	return 0;
}
int main(void)
{
	float p[max+1]={0,0.15,0.10,0.05,0.10,0.20};
	float q[max+1]={0.05,0.10,0.05,0.05,0.05,0.10};
	float e[max+2][max+1];
	float ans;
	int root[max+2][max+1],n;//can be reduced to [max+1][max+1]	
	n=5;
	ans=optimal_bst2(p,q,e,root,n);
	printf("%f\n",ans);
	struct node *troot;
	troot=(struct node *)malloc(sizeof(struct node));
	construct_optimal_bst(root,troot,1,n);
	print(troot);
	printf("\n");
	return 0;
}
