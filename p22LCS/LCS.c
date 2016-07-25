#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max 100
const char lu[4]={0xe2,0x86,0x96},u[4]={0xe2,0x86,0x91},l[4]={0xe2,0x86,0x90};
int LCS_LENGTH(char x[],char y[],int c[][max+1],int b[][max+1],int m,int n)
{
	int i,j;
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
			if (x[i-1]==y[j-1])
			{
				c[i][j]=c[i-1][j-1]+1;
				b[i][j]=1;
			}
			else
				c[i][j]=c[i-1][j]>=c[i][j-1]?(b[i][j]=2,c[i-1][j]):(b[i][j]=3,c[i][j-1]);
	return c[m][n];
}
int printb(int b[][max+1],int m,int n)
{
	int i,j;
	for (i=1;i<=m;i++)
	{
		for (j=1;j<=n;j++)
			switch(b[i][j]){
				case 1:printf("%s ",lu);break;
				case 2:printf("%s ",u);break;
				case 3:printf("%s ",l);break;
				default:break;
			}
		printf("\n");
	}
	return 0;
}
int printc(int c[][max+1],int m,int n)
{
	int i,j;
	for (i=1;i<=m;i++)
	{
		for (j=1;j<=n;j++)
			printf("%d ",c[i][j]);
		printf("\n");
	}
	return 0;
}
int printLCS(char x[],char y[],int c[][max+1],int i,int j)
{
	if ((i==0)||(j==0))
		return 0;
	if (x[i-1]==y[j-1])
	{
		printLCS(x,y,c,i-1,j-1);
		printf("%c",x[i-1]);
	}
	else
		if (c[i-1][j]>=c[i][j-1])
			printLCS(x,y,c,i-1,j);
		else
			printLCS(x,y,c,i,j-1);
	return 0;
}
int printAllLCS(char x[],char y[],int c[][max+1],char s[],int i,int j,int l)
{
	if ((i==0)||(j==0))
	{
		printf("%s\n",s);
		return 0;
	}
	if (x[i-1]==y[j-1])	
	{
		s[l]=x[i-1];
		printAllLCS(x,y,c,s,i-1,j-1,l-1);
		return 0;
	}
	else
		if (c[i-1][j]==c[i][j-1])//当两者相同时，意味着可以由两者继承过来，对应两种选择
		{
			printAllLCS(x,y,c,s,i-1,j,l);
			printAllLCS(x,y,c,s,i,j-1,l);
		}
		else
			if (c[i-1][j]>c[i][j-1])
				printAllLCS(x,y,c,s,i-1,j,l);
			else
				printAllLCS(x,y,c,s,i,j-1,l);
	return 0;
}
int LCS_LENGTH2(char x[],char y[],int c2[][max+1],int b[][max+1],int m,int n)//实际上求LCS长度只用两行，但这样不足以记录LCS
{
	int i,j;
	for (i=1;i<=m;i++)
		for (j=1;j<=n;j++)
			if (x[i-1]==y[j-1])
			{
				c2[i%2][j]=c2[(i-1)%2][j-1]+1;
				b[i][j]=1;
			}
			else
				c2[i%2][j]=c2[(i-1)%2][j]>=c2[i%2][j-1]?(b[i][j]=2,c2[(i-1)%2][j]):(b[i][j]=3,c2[i%2][j-1]);
	return c2[m%2][n];
}
int main(void)
{
	char x[max]="ABCBDAB",y[max]="BDCABA",s[max];
	int c[max+1][max+1],b[max+1][max+1]/*记录继承关系*/,i,j,m,n;
	m=strlen(x);
	n=strlen(y);
	for (i=0;i<=m;i++)
		c[i][0]=0;
	for (j=0;j<=n;j++)
		c[0][j]=0;
	int ans;
	ans=LCS_LENGTH(x,y,c,b,m,n);
	printf("%d\n",ans);
	printb(b,m,n);
	printc(c,m,n);
	printLCS(x,y,c,m,n);
	printf("\n");
	s[ans]='\0';
	printAllLCS(x,y,c,s,m,n,ans-1);
	int c2[2][max+1];
	for (i=0;i<=n;i++)
		c2[0][i]=0;
	c2[1][0]=0;
	ans=LCS_LENGTH2(x,y,c2,b,m,n);
	printf("%d\n",ans);
	return 0;
}
