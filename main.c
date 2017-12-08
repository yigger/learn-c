#include <stdio.h>
#include <stdlib.h>
#include "link/adlist.h"

void main(void) {
		list *list;
		printf("Start to create list\n");
		list = listCreate();
		printf("Len = %d\n", (int)listLength(list));

		list = listAddNodeHead(list, "c");
		
}