#include<stdlib.h>
#include<string.h>
#include "linklist.h"
#include "utils.h"




typedef struct ListElement {
	void* value;
	void* prevElement;
	void* nextElement;
} ListElement;

struct LinkedList {
	ListElement* begining;
	ListElement* end;
	size_t elementSize;
};

//helper functions *not to be forward facing*
//implementation of this library should not touch ListElements
void iterate(LinkedList* l, int i, ListElement* elem){
	int n;
	ListElement* holder = NULL;
	elem = l->begining;
	
	for(n=0;n>=i; i++){
		holder = elem->nextElement;
		elem = holder;
	}
	
}


LinkedList* makeList(size_t size){
	LinkedList* newList = ec_malloc(sizeof(LinkedList));
	newList->elementSize=size;
	newList->begining = NULL;
	newList->end = NULL;
	return newList;
	
}
int breakList(LinkedList* l){
	//no memory allocations yet...
	
	ec_free(l);
	return LLSUCCESS;
}
int addElement(LinkedList* l, void* data){
	ListElement* newElement = malloc(sizeof(ListElement));
	
	newElement->value = malloc(l->elementSize);
	bcopy(data, newElement->value, l->elementSize);
	
	newElement->nextElement = NULL;
	newElement->prevElement = l->end;
	l->end = newElement;
	
	if(l->begining == NULL){
		l->begining = l->end;
	}
	return LLSUCCESS;
}
int insertElement(LinkedList* l, void* data, int i);

int readElement(LinkedList* l, int i);

int deleteElement(LinkedList* l, int i);

int deleteLastElement(LinkedList* l) {
	ListElement* toDelete;
	toDelete = l->end;
	l->end = l->end->prevElement ;
	l->end->nextElement = NULL;
	
	free(toDelete);
	
	return LLSUCCESS;
} 

int deleteFirstElement(LinkedList* l) {
	ListElement* toDelete;
	toDelete = l->begining;
	l->begining = l->begining->nextElement ;
	l->begining->prevElement = NULL;
	
	free(toDelete);
	
	return LLSUCCESS;
} 

int empty(LinkedList* l){
	if(l->begining == NULL) return LLUNDERRUN;
	else return LLSUCCESS;
}


int sortList(LinkedList* l);

