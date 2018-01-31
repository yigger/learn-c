#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEVEL 5

#define TRUE 1
#define FALSE 0

typedef struct skipNode {
  int val;
  struct skipNode *next;
  struct skipNode *down;
} skipnode;

typedef struct skipList {
  struct skipNode *head;
  int level;
  int length;
} skipList;

skipList *createSkipList() {
  skipList *skiplist;
  skiplist = (skipList*)malloc(sizeof(skipList));
  if(skiplist == NULL) {
    printf("malloc fail");
    exit(0);
  }

  skiplist->head = NULL;
  skiplist->level = 1;
  skiplist->length = 0;
  return skiplist;
}

int randowlevel () {
  int k = 1;
  srand((unsigned)time(0));
  while(rand() % 2) {
    k++;
  }
  return k >= MAX_LEVEL ? MAX_LEVEL : k;
}

int insertNode (skipList *skiplist, int value) {
  // int level = randowlevel();
  int randHeight = 3;
  int level = skiplist->level;
  int size = skiplist->level;
  int j = 0;
  skipnode *node = skiplist->head;
  int p[j];

  while(node) {
    while(node) {
      if(node->val < value) {
        p[j] = node;
        j++;
        break;
      } 
      node = node->next;
    }
    node = node->down;
  }

  

  return TRUE;
}

int main() {
  skipList *skiplist;
  skiplist = createSkipList();
  insertNode(skiplist, 1);
  // insertNode(skiplist, 5);
  return 0;
}