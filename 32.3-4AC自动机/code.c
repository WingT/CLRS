#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxn 1000
#define maxm 100
typedef struct node{
	int ok;/*节点对应的模式串编号*/
	struct node *p,*s[26],*fail;/*p为父节点指针,s为子节点指针数组,限制为小写字母,fail为跳转指针,相当于π函数*/
}node;
typedef struct AC{
	int n;/*模式串个数*/
	node *root;/*trie树根,相当于KMP算法中的0(长度为0,也就是空串)*/
	char p[maxn][maxm];/*模式串*/
}AC;
node *newnode(void)
{
	node *New;
	New=(node *)malloc(sizeof(node));
	New->ok=-1;/*初始化节点不代表任何模式串*/
	New->p=NULL;
	New->fail=NULL;
	int i;
	for (i=0;i<26;i++)
		New->s[i]=NULL;
	return New;
}
int *insert(node *root,char p[],int i)
{
	int m=strlen(p),k;
	node *now=root;
	for (k=0;k<m;k++)
	{
		int idx=(int)(p[k]-'a');/*p[k]对应的s数组下标,下同*/
		if (!now->s[idx])/*如果s[idx]是NULL,说明now后面没有p[k]这个字母*/
		{
			node *New=newnode();
			New->p=now;
			now->s[idx]=New;
		}
		now=now->s[idx];
	}
	now->ok=i;/*保存模式串的编号,此时now是p中最后一个字母的位置*/
	return 0;
}
int computfail(AC ac)/*计算π函数,和KMP算法很相似*/
{
	int i,n=ac.n;
	char (*p)[maxm]=ac.p;/*为了方便,令p=ac.p,这是数组指针*/
	node *root=ac.root;
	for (i=0;i<n;i++)/*相当于对每个模式串运行一次comput_prefix_function,只是KMP中π是数字的形式,这里是指针*/
	{
		int k,idx;
		node *now;
		now=root;
		idx=(int)(p[i][0]-'a');
		now->s[idx]->fail=root;/*相当于令π[1]=0*/
		now=now->s[idx];/*相当于KMP中的q*/
		node *pre=root;/*相当于KMP中的k,即π[q-1]*/
		for (k=1;k<strlen(p[i]);k++)/*for q=2 to m*//*k(字符串下标,和now是等同的,也和KMP中的q是等同的(由于字符串从0开始,相差1))*/
		{
			idx=(int)(p[i][k]-'a');
			now=now->s[idx];
			while (pre!=root&&pre->s[idx]==NULL)/*while (k>0&&p[k+1]!=p[q])*/
				pre=pre->fail;/*k=π(k)*/
			if (pre->s[idx])/*if (p[k+1]==p[q])*/
				pre=pre->s[idx];/*k++*/
			now->fail=pre;/*π[q]=k*/
		}
	}
	return 0;
}
int match(AC ac,char t[])
{
	int m=strlen(t),i;
	node *root=ac.root;
	node *pre=root;/*q=0*/
	for (i=0;i<m;i++)
	{
		int idx=(int)(t[i]-'a');
		while (pre!=root&&pre->s[idx]==NULL)
			pre=pre->fail;
		if (pre->s[idx])
			pre=pre->s[idx];/*上面的注释同computfail*/
		if (pre->ok!=-1)
			printf("%s: %d\n",ac.p[pre->ok],i-strlen(ac.p[pre->ok])+1);/*输出匹配的模式串和对应的起始位置(从0开始)*/
		/*这里和书上的KMP算法略有不同,书上令q=π[q]是为了避免下次匹配时第6行数组越界,但是这里不存在这个问题,因为只需要判断节点某孩子的指针是否为空就可以断定两个字符是否匹配,相反,如果这里采取和书上一样的措施,结果可能有错,因为模式串中可能存在前缀包含,比如an和and,匹配完了an将不能匹配到and*/
	}
	return 0;
}
AC initac(void)
{
	AC ac;
	int n,i;
	scanf("%d",&n);
	ac.n=n;
	ac.root=newnode();
	ac.root->p=ac.root;
	ac.root->fail=ac.root;
	for (i=0;i<n;i++)
	{
		scanf("%s",ac.p[i]);
		insert(ac.root,ac.p[i],i);
	}
	return ac;
}
int main(void)
{
	char t[maxn];
	scanf("%s",t);
	AC ac;
	ac=initac();
	computfail(ac);
	match(ac,t);
	return 0;
}
