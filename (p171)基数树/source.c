#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 100
struct node{
	int f;
	struct node *l,*r;
};
void insert(struct node *root,char s[],int dep)
{
	struct node *new;
	if (dep==strlen(s))
		root->f=1;
	else
		if (s[dep]=='0')
		{
			if (root->l==NULL)
			{
				new=(struct node *)malloc(sizeof(struct node));
				new->l=NULL;
				new->r=NULL;
				new->f=0;
				root->l=new;
				insert(new,s,dep+1);
			}
			else
				insert(root->l,s,dep+1);
		}
		else
		{
			if (root->r==NULL)
			{
				new=(struct node *)malloc(sizeof(struct node));
				new->l=NULL;
				new->r=NULL;
				new->f=0;
				root->r=new;
				insert(new,s,dep+1);
			}
			else
				insert(root->r,s,dep+1);
		}
}
void print(char s[],int l)
{
	int i;
	for (i=0;i<l;i++)
		printf("%c",s[i]);
	printf("\n");
}
void sort(struct node *root,char s[],int dep)
{
	if (root->f==1)
		print(s,dep);
	if (root->l!=NULL)
	{
		s[dep]='0';
		sort(root->l,s,dep+1);
	}
	if (root->r!=NULL)/*回溯*/
	{
		s[dep]='1';
		sort(root->r,s,dep+1);
	}
}
int main(void)
{
	int n,i;
	char s[max];
	struct node *root;
	root=(struct node *)malloc(sizeof(struct node));
	root->f=0;
	root->l=NULL;
	root->r=NULL;
	scanf("%d",&n);
	for (i=0;i<n;i++)
	{
		scanf("%s",s);
		insert(root,s,0);
	}
	sort(root,s,0);
	return 0;
}
