#include<stdio.h>
#include<string.h>
#define maxm 1000
typedef struct e{
	char letter;/*字符(不包括)*/
	int end;/*如果字符后面是*号,标记end为1*/
	int fail;/*相当于π函数*/
}e;
typedef struct MAC{
	int n;/*非*字符的个数*/
	e p[maxm+1];
}MAC;
MAC initmac(void)
{
	char p[maxm];
	scanf("%s",p);
	int i,l,k=0;
	l=strlen(p);
	MAC mac;
	mac.p[0].end=1;/*特殊情况,置0*/
	for (i=0;i<l;i++)
		if (p[i]!='*')
		{
			k++;
			mac.p[k].end=0;
			mac.p[k].letter=p[i];
		}
		else
			mac.p[k].end=1;
	mac.n=k;
	return mac;
}
int computfail(MAC *mac)/*这里一定要用指针,因为结构作为参数传递时,是复制内存*/
{
	int q,i;
	int n=mac->n;
	e *p=mac->p;
	q=0;
	for (i=1;i<=n;i++)
		if (p[i].end)/*如果后面是*号,fail指向自己*/
		{
			p[i].fail=i;
			q=i;
		}
		else
			if (p[i-1].end)/*指向前面的最后一个字符,相当于KMP算法中的初始化*/
			{
				p[i].fail=i-1;
				q=i-1;
			}
			else/*和KMP算法一样,即对单个字符串计算π函数*/
			{
				while ((!p[q].end)&&(p[q+1].letter!=p[i].letter))
					q=p[q].fail;
				if (p[q+1].letter==p[i].letter)
					q++;
				p[i].fail=q;
			}
	return 0;
}
int match(MAC *mac,char t[])/*和KMP算法中的匹配几乎一样*/
{
	int i,l=strlen(t),q=0;
	int n=mac->n;
	e *p=mac->p;
	for (i=0;i<l;i++)
	{
		while ((!p[q].end)&&(p[q+1].letter!=t[i]))
			q=p[q].fail;
		if (p[q+1].letter==t[i])
			q++;
		if (q==n)
			return 1;/*和书上的KMP匹配的时候不一样,这里直接退出即可,实际上不退出也只能找到前面相同,最后一个部分出现位置不同*/
	}
	return 0;
}
int main(void)
{
	char t[maxm];
	scanf("%s",t);
	MAC mac;
	mac=initmac();
	computfail(&mac);
	int ans;
	ans=match(&mac,t);
	printf("%d\n",ans);
	return 0;
}
