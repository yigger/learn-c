#include <stdio.h>
#include <stdlib.h>
#include "src/adlist.h"
#include "src/sds.h"

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
	printf("%s", sdsnewlen(a, 5));

	return 0;
}
