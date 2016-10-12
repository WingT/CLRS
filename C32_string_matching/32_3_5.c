#include<stdio.h>
#include<stdlib.h>
typedef struct trie_node{
  char ch;
  int status;
  struct trie_node *fail,*succ[128];
}trie_node;
trie_node *new_trie_node(){
  trie_node *root=(trie_node *)malloc(sizeof(trie_node));
  root->fail=NULL;
  for (int i=0;i<128;i++)
    root->succ[i]=NULL;
  root->status=0;
  return root;
}
trie_node *generate_automaton(char p[]){
  trie_node *root=new_trie_node();
  root->fail=root;
  trie_node *pre=root;
  for (int i=0;p[i];i++){
    if (p[i]!='*'){
      trie_node *new_node=new_trie_node();
      pre->succ[p[i]]=new_node;
      new_node->ch=p[i];
      if (!p[i+1])
        new_node->status=1;
      if (pre==pre->fail)
        new_node->fail=pre;
      else{
        trie_node *tmp=pre->fail;
        while (tmp!=tmp->fail && !tmp->succ[p[i]])
          tmp=tmp->fail;
        if (tmp->succ[p[i]])
          tmp=tmp->succ[p[i]];
        new_node->fail=tmp;
      }
      pre=new_node;
    }
    else
      pre->fail=pre;
  }
  return root;
}
void match(char p[],char t[]){
  trie_node *root=generate_automaton(p),*q=root;
  for (int i=0;t[i];i++){
    while (q!=q->fail && !q->succ[t[i]])
      q=q->fail;
    if (q->succ[t[i]])
      q=q->succ[t[i]];
    if (q->status)
      printf("%d\n",i);
  }
  return 0;
}
int main(int argc,char **argv){
  if (argc!=3){
    printf("usage: %s pattern text\n",argv[0]);
  }
  else match(argv[1],argv[2]);
  return 0;
}
