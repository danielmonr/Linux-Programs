#include "helpers.h"
#include <iostream>

int main(int argc, char* argv[]){
	dlist_t* list = DList();
	addNode(list, 1);
	addNode(list, 2);
	printDList(list);
	addNode(list, 3);
	printDList(list);
	deleteAt(list, 0);
	printDList(list);
	addNode(list,4);
	eraseDList(list);

	return 0;
}