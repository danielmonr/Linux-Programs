#include <iostream>
#include <stdio.h>
#include <stdlib.h>

struct node{
    int val;
    struct node* prev;
    struct node* next;
};
typedef struct node node_t;

struct dlist{
    node_t* start;
    int length;
};
typedef struct dlist dlist_t;

dlist_t* DList(){
    dlist_t* list = (dlist_t*) malloc (sizeof(dlist_t));
    list->length = 0;
    list->start = NULL;
}

node_t* lastNode(dlist_t* l){
	if(l->length == 0)
		return NULL;
    node_t* n = l->start;
    while(n->next){
        n = n->next;
    }
    return n;
}

void addNode(dlist_t* l, int v){
    node_t* n = (node_t*) malloc (sizeof(node_t));
    n->val = v;
    n->next = NULL;
    node_t* last = lastNode(l);
	if(last){
    	last->next = n;
    	n->prev = (last)? last : NULL;
	}
	else{
		l->start = n;
	}
    l->length = l->length +1;
}

node_t* nodeAt(dlist_t* l, int i){
    if(l->length <= i || i < 0)
        return NULL;
    node_t *res = l->start;
    for (int it = 1; it <= i; ++it){
        res = res->next;
    }
    return res;
}

void deleteAt(dlist_t *l, int i){
    if(l->length <= i || i < 0){
        std::cout << "Error: No such node\n";
        return;
    }
    node_t* del = nodeAt(l, i);
    node_t* nex = del->next;
    if(i>0){
        node_t* pre = del->prev;
        pre->next = nex;
        nex->prev = pre;
    }
    else{
        l->start = nex;
        nex->prev = NULL;
    }
    del->next = NULL;
    del->prev = NULL;
    free(del);
    l->length = l->length-1;
}

void printDList(dlist_t *l){
    int i = 0;
    node_t* n = l->start;
    while(i < l->length-1){
        std::cout << n->val << "->";
        n = n->next;
		++i;
    }
    std::cout << n->val << std::endl;
}

void eraseDList(dlist_t* l){
	int i = 0;
	node_t* n = l->start;
    while(i < l->length){
		node_t* nex = n->next;
        free(n);
		n = nex;
		++i;
    }
	free(l);
}