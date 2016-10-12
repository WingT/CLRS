#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAXARG 1000
typedef struct trie_node{
  char ch;
  char *pattern;
  struct trie_node *fail,*succ[128];
}trie_node;
trie_node *new_trie_node(void){
  trie_node *new_node=(trie_node *)malloc(sizeof(trie_node));
  new_node->pattern=NULL;
  new_node->fail=NULL;
  for (int i=0;i<128;i++)
    new_node->succ[i]=NULL;
  return new_node;
}
void compute_fail(trie_node *root){
  trie_node *que[MAXARG];
  int head=0,tail=-1,count=0;
  for (int i=0;i<128;i++)
    if (root->succ[i]){
      root->succ[i]->fail=root;
      tail=(tail+1)%MAXARG;
      que[tail]=root->succ[i];
      count++;
    }
  while (count){
    trie_node *pre=que[head];
    for (int i=0;i<127;i++){
      if (pre->succ[i]){
        trie_node *tmp=pre->fail;
        while (tmp!=root && !tmp->succ[i])
          tmp=tmp->fail;
        if (tmp->succ[i])
          tmp=tmp->succ[i];
        pre->succ[i]->fail=tmp;
        tail=(tail+1)%MAXARG;
        que[tail]=pre->succ[i];
        count++;
      }
    }
    head=(head+1)%MAXARG;
    count--;
  }
}
trie_node *generate_automaton(char *ps[]){
  trie_node *root=new_trie_node();
  for (int i=0;ps[i];i++){
    trie_node *tmp=root;
    char *p=ps[i];
    for (int j=0;p[j];j++){
      if (!tmp->succ[p[j]]){
        trie_node *new_node=new_trie_node();
        new_node->ch=p[j];
        if (!p[j+1])
          new_node->pattern=p;
        tmp->succ[p[j]]=new_node;
        tmp=new_node;
      }
      else{
        tmp=tmp->succ[p[j]];
        if (!p[j+1])
          tmp->pattern=p;
      }
    }
  }
  compute_fail(root);
  return root;
}
void automaton_matcher(char *ps[],char t[]){
  trie_node *root=generate_automaton(ps),*q=root;
  for (int i=0;t[i];i++){
    while (q!=root && !q->succ[t[i]])
      q=q->fail;
    if (q->succ[t[i]])
      q=q->succ[t[i]];
    if (q->pattern){
      trie_node *tmp=q;
      while (tmp->pattern){
        printf("%d : %s\n",i-strlen(tmp->pattern)+1,tmp->pattern);
        tmp=tmp->fail;
      }
      int flag=1;
      for (int i=0;i<127;i++)
        if (q->succ[i])
          flag=0;
      if (flag)
        q=q->fail;
    }
  }
}
int main(int argc,char **argv){
  if (argc<3){
    printf("usage:%s text pattern1 pattern2 ...\n",argv[0]);
    return 0;
  }
  else automaton_matcher(argv+2,argv[1]);
}
