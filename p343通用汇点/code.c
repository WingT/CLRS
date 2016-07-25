#include<stdio.h>
#include<stdlib.h>
int unviversalsink(short **a,int v)
{
	int i=0,j=0;
	while ((i<v)&&(j<v))
		if (a[i][j]==1)
			i++;
		else
			j++;
	if (i<v)
	{
		for (j=0;j<v;j++)
			if (a[i][j]==1)
				return -1;
		for (j=0;j<v;j++)
			if ((i!=j)&&(a[j][i]!=1))
				return -1;
		return i;
	}
}
int main(void)
{
	short **a;
	int v,e,i,j,x,y,ans;
	scanf("%d%d",&v,&e);
	a=(short **)malloc(sizeof(short *)*v);
	for (i=0;i<v;i++)
	{
		a[i]=(short *)malloc(sizeof(short)*v);
		for (j=0;j<v;j++)
			a[i][j]=0;
	}
	for (i=1;i<=e;i++)
	{
		scanf("%d%d",&x,&y);
		a[x][y]=1;
	}
	ans=unviversalsink(a,v);
	if (ans==-1)
		printf("no answer\n");
	else
		printf("%d\n",ans);
	return 0;
}
