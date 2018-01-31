#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEVEL 5

#define TRUE 1
#define FALSE 0

typedef struct skipNode {
  unsigned long val;
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

int insertNode () {

  

  return TRUE;
}

int main() {
  skipList *skiplist;
  skiplist = createSkipList();
  int level = randowlevel();
  printf("%d", level);
  return 0;
}