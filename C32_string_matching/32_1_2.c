#include<stdio.h>
#include<string.h>
int main(int argc,char **argv)
{
  if (argc!=3)
    {
      printf("usage: %s text pattern\n",argv[0]);
      return 1;
    }
  else
    {
      char *t=argv[1],*p=argv[2];
      int t_len=strlen(t),p_len=strlen(p);
      int i=0;
      int ans[1000],count=0;
      while (i<t_len)
        {
          int j=0;
          while (j<p_len && i<t_len && t[i]==p[j])
            {
              i++;
              j++;
            }
          if (j==0)
            i++;
          else
            if (j==p_len)
              ans[count++]=i-j;
        }
      for (int i=0;i<count;i++)
        printf("%d ",ans[i]);
      printf("\n");
      return 0;
    }
}
