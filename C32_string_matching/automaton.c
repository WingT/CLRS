#include<stdio.h>
#include<string.h>
#define MAXLINE 1000
int delta[MAXLINE][128];
void compute_transition_function(char p[]){
  int p_len=strlen(p);
  for (int q=0;q<=p_len;q++){
    for (int a=0;a<128;a++){
      for (int k=q+1<p_len?q+1:p_len;k>=0;k--){
        int is_suffix=1;
        if (p[k-1]==a){
          for (int j=0;j<k-1;j++){
            if (p[j]!=p[q-k+1+j]){
              is_suffix=0;
              break;
            }
          }
        }
        else is_suffix=0;
        if (is_suffix){
          delta[q][a]=k;
          break;
        }
      }
    }
  }
}
int finite_automation_matcher(char t[],int p_len){
  int t_len=strlen(t),q=0,ans=1;
  for (int i=0;i<t_len;i++){
    q=delta[q][t[i]];
    if (q==p_len){
      printf("%d ",i-p_len+1);
      ans=0;
    }
  }
  return ans;
}
int main(int argc,char **argv){
  if (argc!=3){
    printf("usage:%s pattern text\n",argv[0]);
    return 1;
  }
  else{
    compute_transition_function(argv[1]);
    return finite_automation_matcher(argv[2],strlen(argv[1]));
  }
}
