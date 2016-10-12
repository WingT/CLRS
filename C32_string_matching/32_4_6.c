#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE 1000
int pi[MAXLINE];
void compute_prefix_function(char p[]){
  int p_len=strlen(p);
  int k=0;
  pi[1]=0;
  for (int i=2;i<=p_len;i++){
    while (k && p[k]!=p[i-1])
      k=pi[k];
    if (p[k]==p[i-1])
      k++;
    pi[i]=k;
  }
  for (int i=1;i<p_len;i++){
    if (!(pi[i]==0||p[pi[i]]!=p[i]))
      pi[i]=pi[pi[i]];
  }
}
void kmp_matcher(char p[],char t[]){
  int p_len=strlen(p),t_len=strlen(t),q=0;
  for (int i=0;i<t_len;i++){
    while (q && p[q]!=t[i])
      q=pi[q];
    if (p[q]==t[i])
      q++;
    if (q==p_len){
      q=pi[q];
      printf("%d ",i-p_len+1);
    }
  }
}
int main(int argc, char *argv[]){
  if (argc!=3){
    printf("usage:%s pattern text\n",argv[0]);
    return 1;
  }
  else{
    compute_prefix_function(argv[1]);
     kmp_matcher(argv[1],argv[2]);
    return 0;
  }
}
