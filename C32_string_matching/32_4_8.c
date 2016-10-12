#include<stdio.h>
#include<string.h>
#define MAXLINE 1000
int delta[MAXLINE][128];
int pi[MAXLINE];
void compute_prefix_fucntion(char p[]){
  int p_len=strlen(p),k=0;
  pi[1]=0;
  for (int i=2;i<=p_len;i++){
    while (k && p[k]!=p[i-1])
      k=pi[k];
    if (p[k]==p[i-1])
      k++;
    pi[i]=k;
  }
}
void compute_transition_function(char p[]){
  int p_len=strlen(p);
  compute_prefix_fucntion(p);
  delta[0][p[0]]=1;
  for (int i=1;i<p_len;i++){
    for (int a=0;a<128;a++){
      if (p[i]==a)
        delta[i][a]=i+1;
      else
        delta[i][a]=delta[pi[i]][a];
    }
  }
  for (int a=0;a<128;a++)
    delta[p_len][a]=delta[pi[p_len]][a];
}
int finite_automaton_matcher(char p[],char t[]){
  int p_len=strlen(p),t_len=strlen(t),q=0;
  compute_transition_function(p);
  for (int i=0;i<t_len;i++){
    q=delta[q][t[i]];
    if (q==p_len){
      printf("%d ",i-p_len+1);
    }
  }
}
int main(int argc,char **argv){
  if (argc!=3){
    printf("usage: %s pattern text\n",argv[0]);
    return 1;
  }
  else finite_automaton_matcher(argv[1],argv[2]);
  return 0;
}
