#include <stdio.h>
#include <stdlib.h>
#include "src/adlist.h"
#include "src/sds.h"
#include "src/dict.h"
int main() {
	list *list;

	/*
	此部分是测试双向无环链表
	*/
	printf("Start to test adlist\n");
	list = listCreate();

	list = listAddNodeHead(list, "cccb");
	printList(list);

	list = listAddNodeTail(list, "ab");
	printList(list);
	
	listInsertNode(list, list->head, "test", AL_START_HEAD);
	printList(list);

	listInsertNode(list, list->head, "addToTail", AL_START_TAIL);
	printList(list);

	listNode *searchNode;
	searchNode = listSearchKey(list, "addToTail");
	if(searchNode != NULL) {
		listInsertNode(list, searchNode, "afterInsertValue", AL_START_TAIL);
		printList(list);
	} else {
		printf("can't search node\n");
	}
	
	listDelNode(list, searchNode);
	printList(list);

	/**
	 * 测试字符串
	*/
    char a[3] = "abc";
    sds sds1 = sdsnewlen(a, 5);
	printf("%s", sds1);

    char test[] = "abbb c";
    // printf("大小： %d\n", sdslen(sdsnew(test)));

    sdsfree(sds1);
    printf("after free: %s\n", sds1);

    sds dupstr = sdsdup(test);
    printf("copy test str: %s \n", dupstr);

	/**
	 * 字典
	*/ 
	dict *dt = dictCreate(NULL, NULL);
	

	return 0;
}
