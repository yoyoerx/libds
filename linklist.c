#include<stdlib.h>
#include<string.h>
#include "linklist.h"
#include "utils.h"

//ListElement is a struct (this is also a datatype for ease of use) contains
//			implementations of this library should not touch ListElements
// value : a pointer to alloccated memory of size LinkedList->elementSize
// prevElement : a pointer to the ListElement directly before IT in the linked list
//                 and is NULL if THIS is the first element in the list
// nextElement : a pointer to the ListElement directly after IT it the linked list
//                 and is NULL if THIS is the last element in the list 
typedef struct ListElement {
	void* value;
	void* prevElement;
	void* nextElement;
} ListElement;

//LinkedList is a struct which contains the guts of the linked list.
//			and is also defined as a datatype in linklist.h
//begining : a pointer to the first ListElement in the list
//end : a pointer to the last ListElement in the list
//			if the list is Empty, begining and end both point to NULL
//			if the list has one element, begining and end point to the same ListElement
//elementSize : the size of the elements being stored in the LinkedList
//			user supplied and assumed to be correct for the data they are storing
struct LinkedList {
	ListElement* begining;
	ListElement* end;
	size_t elementSize;
};

//private helper functions *not to be forward facing*///////////////////////////////

//iterate() provides the ith element of a LinkedList
//l : a pointer to the LinkedList
//i : an integer number of elements to traverse befor returning
//returns : a pointer to the ith ListElement
//			if i==0, returns l->begining
//			if i>number of elements, returns NULL
ListElement* iterate(LinkedList* l, int i){
	int n;
	ListElement* holder = NULL;
	holder = l->begining;
	
	for(n=0;n>=i; i++){
		holder = holder->nextElement;
	}
	
	return holder;
}

//createElement() creates a new ListElement for insertion in to the LinkedList
//data : a pointer to the data to be added
//			assumes that data is correctly sized based on size
//returns : a new ListElement with NULL pointers to the previous and next elements
//			fails fatally if memory cannot be allocated
ListElement* createElement(void* data, size_t size){
	ListElement* newElement = ec_malloc(sizeof(ListElement));
	
	newElement->value = ec_malloc(size);
	bcopy(data, newElement->value, size);
	
	newElement->nextElement = NULL;
	newElement->prevElement = NULL;

	return newElement;
}

//delete() deletes an existing ListElement
//toDelete : a pointer to the ListElement to delete
//returns : a  status code as defined in linklist.h
//			fails fatally if pointer toDelete is NULL
int delete(ListElement* toDelete){
	ec_free(toDelete->value);
	ec_free(toDelete);
	return LLSUCCESS;
}

//PUBLIC FUNCTIONS//////////////////////////////////////////////////////////////////

//makeList() initalizes a LinkedList
//size : the size of the elements which will go in the list
//			this is user supplied and is assumed to be correct
//returns : a pointer to a LinkedList with 0 elements
//			fails fatally if it cannot allocate memory
LinkedList* makeList(size_t size){
	LinkedList* newList = ec_malloc(sizeof(LinkedList));
	newList->elementSize=size;
	newList->begining = NULL;
	newList->end = NULL;
	return newList;
}

//breakList() deallocates all memory used in a LinkedList
//l : a pointer to the LinkedList to be deallocated
//returns : a status code as defined in linklist.h
int breakList(LinkedList* l){
	while(isEmpty(l)==LLSUCCESS){
		deleteLastElement(l);
	}
	ec_free(l);
	return LLSUCCESS;
}

//addElement() adds data to the end of the list
//l : a pointer to the LinkedList to add the data to
//data : a pointer to the data to be added
//			assumes that data is correctly sized based on l->elementSize
//returns : a  status code as defined in linklist.h
int addElement(LinkedList* l, void* data){
	ListElement* newElement = createElement(data, l->elementSize);

	newElement->nextElement = NULL;
	newElement->prevElement = l->end;
	l->end = newElement;
	
	if(l->begining == NULL){
		l->begining = l->end;
	}
	return LLSUCCESS;
}

//insertElement() adds data at an arbitraty location, i, in the list
//l : a pointer to the LinkedList to add the data to
//data : a pointer to the data to be added
//			assumes that data is correctly sized based on l->elementSize
//i : the data added becomes the ith ListElement
//returns : a  status code as defined in linklist.h
int insertElement(LinkedList* l, void* data, int i){
	ListElement* newElement = createElement(data, l->elementSize);
	ListElement* oldIthElement= iterate(l, i);

	newElement->prevElement = oldIthElement->prevElement;
	newElement->nextElement = oldIthElement;
	oldIthElement->prevElement = newElement;

	ListElement* beforeInsert = newElement->prevElement;
	beforeInsert->nextElement = newElement;

	return LLSUCCESS;
}

//readElement() provides a copy of the data in ListElement i
//l : a pointer to the LinkedList to read the data from
//data : a pointer to memory allocated to accept the data from the list
//			assumes that data is correctly sized based on l->elementSize
//i : the data will be read from the ith element of the list
//returns : a  status code as defined in linklist.h
//			if i>number of elements, data is not changed and returns LLUNDERRUN
int readElement(LinkedList* l, void* data, int i){
	ListElement* toRead = iterate(l,i);
	if(toRead==NULL) return LLOVERRUN;

	bcopy(toRead->value, data, l->elementSize);
	return LLSUCCESS;
}

//deleteElement() removes the ith element of the list
//l : a pointer to the LinkedList to delete the data from
//i : the data will be deleted from the ith element of the list
//returns : a  status code as defined in linklist.h
int deleteElement(LinkedList* l, int i){
	ListElement* toDelete = iterate(l,i);
	if(toDelete==NULL) return LLOVERRUN;
	ListElement* beforeDelete = toDelete->prevElement;
	ListElement* afterDelete = toDelete->nextElement;

	beforeDelete->nextElement = afterDelete;
	afterDelete->prevElement = beforeDelete;

	delete(toDelete);

	return LLSUCCESS;
}

//deleteLastElement() removes the last element of the list
//l : a pointer to the LinkedList to delete the data from
//returns : a  status code as defined in linklist.h
int deleteLastElement(LinkedList* l) {
	ListElement* toDelete = l->end;
	if(toDelete == NULL) return LLUNDERRUN;
	l->end = l->end->prevElement;
	l->end->nextElement = NULL;
	
	delete(toDelete);
	
	return LLSUCCESS;
} 

//deleteFirstElement() removes the first element of the list
//l : a pointer to the LinkedList to delete the data from
//returns : a  status code as defined in linklist.h
int deleteFirstElement(LinkedList* l) {
	ListElement* toDelete = l->begining;
	if(toDelete == NULL) return LLUNDERRUN;
	l->begining = l->begining->nextElement;
	l->begining->prevElement = NULL;
	
	delete(toDelete);
	
	return LLSUCCESS;
} 

//isEmpty() determines if the list is empty or not
//l : a pointer to the LinkedList to check
//returns : LLSUCCESS if list still has elements
//			or LLUNDERRUN if list is empty
int isEmpty(LinkedList* l){
	if(l->begining == NULL) return LLUNDERRUN;
	else return LLSUCCESS;
}

//sortList() puts the list in increasing order based on the > operator
//			if the data is not suitable for sorting in this way,
//			do not use this method if your data cannot be sorted this way
//l : a pointer to the LinkedList to sort
//returns : a  status code as defined in linklist.h
//			not implimented yet.  always returns LLFAIL if called
int sortList(LinkedList* l){
	return LLFAIL;
}
