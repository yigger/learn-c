#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#define MAX_LEVEL 6

#define TRUE 1
#define FALSE 0

typedef struct skipNode {
  int val;
  struct skipNode **next;
} skipNode;

typedef struct skipList {
  struct skipNode *head;
  int level;
} skipList;

skipList *createSkipList() {
  skipList *skiplist;
  skiplist = (skipList*)malloc(sizeof(skipList));
  skipNode *header = (skipNode*)malloc(sizeof(skipNode));
  if(skiplist == NULL || header == NULL) {
    printf("malloc fail");
    exit(0);
  }

  skiplist->head = header;
  header->val = INT_MAX;
  header->next = (skipNode**)malloc(sizeof(skipNode*) * (MAX_LEVEL + 1));
  for(int i = 0;i < MAX_LEVEL; ++i) {
    header->next[i] = NULL;
  }

  skiplist->level = 1;
  return skiplist;
}

static int rand_level() {
    int level = 1;
    while (rand() < RAND_MAX / 2 && level < MAX_LEVEL)
        level++;
    return level;
}

int insertNode (skipList *skiplist, int value) {
  skipNode *header = skiplist->head;
  skipNode *update[MAX_LEVEL + 1];
  int level = skiplist->level;

  for(int i = level - 1; i >= 0; i--) {
    while(header->next[i] && header->next[i]->val < value) {
      header = header->next[i];
    }
    update[i] = header;
  }

  int k = rand_level();
  printf("k = %d\n", k);
  if(k > skiplist->level) {
    for(int i = skiplist->level; i < k; ++i) {
      update[i] = skiplist->head;
    }
    skiplist->level = k;
  }
  
  skipNode *new = (skipNode *)malloc(sizeof(skipNode));
  new->val = value;
  new->next = (skipNode**)malloc(sizeof(skipNode*) * (skiplist->level + 1));

  for(int i = 0;i < k; ++i) {
    new->next[i] = update[i]->next[i];
    update[i]->next[i] = new;
  }
  return TRUE;
}

static void skiplist_dump(skipList *list) {
    skipNode *x = list->head;
    for(int i = 0;i < list->level; i++) {
      printf("Level %d\n", i);
      while (x && x->next[i] && x->next[i] != list->head) {
          printf("[%d]->", x->next[i]->val);
          x = x->next[i];
      }
      printf("NIL\n");
    }
}

int main() {
  skipList *skiplist;
  skiplist = createSkipList();
  int arr[] = {1,2,3,5,7,9,12,46,50};
  for(int i = 0; i < 9; ++i) {
    insertNode(skiplist, arr[i]);
  }
  skiplist_dump(skiplist);
  return 0;
}