#include<stdio.h>
#include<string.h>
#define MAXLINE 1000
int pi[MAXLINE];
void compute_prefix_function(char p[]){
  int p_len=strlen(p);
  pi[1]=0;
  for (int q=2;q<=p_len;q++){
    int k=pi[q-1];
    while (k && p[k]!=p[q-1])
      k=pi[k];
    if (p[k]==p[q-1])
      k++;
    pi[q]=k;
  }
}
int kmp_matcher(char t[],char p[]){
  int t_len=strlen(t),p_len=strlen(p),q=0,ans=1;
  for (int i=0;i<t_len;i++){
    while (q && p[q]!=t[i])
      q=pi[q];
    if (p[q]==t[i])
      q++;
    if (q==p_len){
      q=pi[q];
      ans=0;
      printf("%d ",i-p_len+1);
    }
  }
  return ans;
}
int main(int argc, char *argv[]){
  if (argc!=3){
    printf("usage:%s pattern text\n",argv[0]);
    return 1;
  }
  else{
    compute_prefix_function(argv[1]);
    return kmp_matcher(argv[2],argv[1]);
  }
}
