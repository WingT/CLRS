/*the basic idea of this algo is:
 * 1: work out each pattern's occurence
 * 2: combine each patterns's occurence*/
#include<stdio.h>
#include<string.h>
#define MAX 100
typedef struct {
  int data[MAX];
  int count;
}loc;
int parse_pattern(char *pattern,char *sub[])
{
  int new_sub=1,i=0,ans=0;
  while (pattern[i])
    {
      if (pattern[i]!='*'){
        if (new_sub)
          {
            sub[ans++]=pattern+i;
            new_sub=0;
          }
      }
      else{
        new_sub=1;
        pattern[i]=0;
      }
      i++;
    }
  return ans;
}
loc match(char *t,char *p){
  int t_len=strlen(t),p_len=strlen(p);
  int count=0;
  loc ans;
  for (int i=0;i<=t_len-p_len;i++)
    {
      int j;
      for (j=0;j<p_len;j++)
        if (t[i+j]!=p[j])
          break;
      if (j==p_len)
        ans.data[count++]=i;
    }
  ans.count=count;
  return ans;
}
void combine(char *sub[],loc loc_sub[],int n,int cur,loc *ans){
  if (cur==n){
    printf("(");
    for (int i=0;i<n-1;i++)
      printf("%d ",ans->data[i]);
    printf("%d)\n",ans->data[n-1]);
  }
  else
    {
      int length_sub;
      if (cur!=0)
        length_sub=strlen(sub[cur-1]);
      for (int i=0;i<loc_sub[cur].count;i++)
        if (cur==0 || ans->data[cur-1]+length_sub <= loc_sub[cur].data[i])
          {
            ans->data[cur]=loc_sub[cur].data[i];
            combine(sub,loc_sub,n,cur+1,ans);
          }
    }
}
int main(int argc, char *argv[])
{
  if (argc!=3)
    {
      printf("usage: %s text pattern\n",argv[0]);
      return 1;
    }
  else
    {
      char *sub[MAX];
      int count_sub=parse_pattern(argv[2],sub);
      loc loc_sub[MAX];
      for (int i=0;i<count_sub;i++)
        loc_sub[i]=match(argv[1],sub[i]);
      loc ans;
      combine(sub,loc_sub,count_sub,0,&ans);
    }
  return 0;
}
