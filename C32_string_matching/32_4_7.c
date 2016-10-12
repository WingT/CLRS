#include<stdio.h>
#include<string.h>
#define MAXLINE 1000
int pi[MAXLINE];
void comput_prefix_function(char p[]){
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
  for (int i=1;i<p_len;i++){
    if (!(pi[i]==0 || p[pi[i]]!=p[i]))
      pi[i]=pi[pi[i]];
  }
}
int kmp_matcher(char p[],char t[]){
  int p_len=strlen(p),t_len=strlen(t),q=0;
  if (p_len!=t_len)
    return 0;
  for (int i=0;i<t_len;i++){
    while (q && p[q]!=t[i])
      q=pi[q];
    if (p[q]==t[i])
      q++;
    if (q==p_len)
      return 1;
  }
  return 0;
}
int is_rotation(char str1[],char str2[]){
  char buf[MAXLINE];
  strcpy(buf,str1);
  strcat(buf,str1);
  return kmp_matcher(str2,buf);
}
int main(int argc,char **argv){
  if (argc!=3){
    printf("usage: %s str1 str2\n",argv[0]);
    return 1;
  }
  else{
    printf("%d",is_rotation(argv[1],argv[2]));
    return 0;
  }
}
