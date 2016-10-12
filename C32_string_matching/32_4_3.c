#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE 1000
int pi[MAXLINE];
void compute_prefix_function(char p[]){
  int p_len=strlen(p);
  pi[1]=0;
  for (int i=2;i<=p_len;i++){
    int k=pi[i-1];
    while (k && p[k]!=p[i-1])
      k=pi[k];
    if (p[k]==p[i-1])
      k++;
    pi[i]=k;
  }
}
void match(char p[],char t[]){
  int p_len=strlen(p),t_len=strlen(t);
  char pt[MAXLINE];
  strcpy(pt,p);
  strcat(pt,t);
  compute_prefix_function(pt);
  int f[MAXLINE];
  f[0]=0;
  for (int i=1;i<p_len;i++)
    f[i]=0;
  f[p_len]=1;
  for (int i=p_len+1;i<=p_len+t_len;i++){
    f[i]=f[pi[i]];
    if (f[i])
      printf("%d ",i-2*p_len);
  }
  printf("\n");
}
int main(int argc, char *argv[]){
  if (argc!=3){
    printf("usage:%s pattern text\n",argv[0]);
    return 1;
  }
  else{
    match(argv[1],argv[2]);
    return 0;
  }
}
