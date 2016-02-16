#include<stdlib.h>
#include<string.h>
#include "linklist.h"
#include "utils.h"



//ListElement is a struct (this is also a datatype for ease of use) contains
//			implementations of this library should not touch ListElements
// value : a pointer to allocated memory of size LinkedList->elementSize
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
//i : an integer number of elements to traverse before returning
//returns : a pointer to the ith ListElement
//			if i<=0, returns l->begining
//			if i>number of elements, returns NULL
ListElement* iterate(LinkedList* l, int i){
	int n;
	ListElement* holder = NULL;
	
	holder = l->begining;
	for(n=1;n<=i; n++){
		if(holder==NULL) return holder;
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

//readElement() reads a ListElement
//e : ListElement to read
//data : a pointer to memory allocated to accept the data from the list
//			assumes that data is correctly sized based on l->elementSize
//size : the size of the data element to be read
//returns : a  status code as defined in linklist.h
//			if e==null, data is not changed and returns LLFAIL
int readElement(ListElement* e, void* data, size_t size){
	if(e==NULL) return LLFAIL;
	bcopy(e->value, data, size);
	return LLSUCCESS;
}

//deleteElement() deletes an existing ListElement
//toDelete : a pointer to the ListElement to delete
//returns : a  status code as defined in linklist.h
//			fails fatally if pointer toDelete is NULL
int deleteElement(ListElement* toDelete){

	if(toDelete==NULL) return LLFAIL;

	ListElement* beforeDelete = toDelete->prevElement;
	ListElement* afterDelete = toDelete->nextElement;

	if(beforeDelete!=NULL) {
		beforeDelete->nextElement = afterDelete;
	}
	
	if(afterDelete!=NULL){
		afterDelete->prevElement = beforeDelete;
	}
	
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
	if(l->end!=NULL) l->end->nextElement = newElement;
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
// 			if i>number of elements, returns LLOVERRUN
//			if i<=0, element is inserted at the begining of the list
//returns : a  status code as defined in linklist.h
int insertElement(LinkedList* l, void* data, int i){
	
	ListElement* oldIthElement = iterate(l, i);
	if(oldIthElement==NULL) {
		oldIthElement = iterate(l,i-1);
		if(oldIthElement==NULL) return LLOVERRUN;
		//case for inserting at end of list
		return addElement(l, data);
	}
		
	ListElement* newElement = createElement(data, l->elementSize);

	newElement->prevElement = oldIthElement->prevElement;
	newElement->nextElement = oldIthElement;
	oldIthElement->prevElement = newElement;

	if(newElement->prevElement==NULL) l->begining = newElement;
	else{
		ListElement* beforeInsert = newElement->prevElement;
		beforeInsert->nextElement = newElement;
	}

	return LLSUCCESS;
}

//readElement() provides a copy of the data in ListElement i
//l : a pointer to the LinkedList to read the data from
//data : a pointer to memory allocated to accept the data from the list
//			assumes that data is correctly sized based on l->elementSize
//i : the data will be read from the ith element of the list
//returns : a  status code as defined in linklist.h
//			if i>number of elements, data is not changed and returns LLUNDERRUN
int readElementI(LinkedList* l, void* data, int i){
	ListElement* toRead = iterate(l,i);
	if(readElement(toRead, data, l->elementSize)==LLFAIL) return LLOVERRUN;
	return LLSUCCESS;
}

int readLastElement(LinkedList* l, void* data){
	ListElement* toRead = l->end;
	if(readElement(toRead, data, l->elementSize)==LLFAIL) return LLOVERRUN;
	return LLSUCCESS;
}

int readFirstElement(LinkedList* l, void* data){
	ListElement* toRead = l->begining;
	if(readElement(toRead, data, l->elementSize)==LLFAIL) return LLUNDERRUN;
	return LLSUCCESS;
}

//deleteElementI() removes the ith element of the list
//l : a pointer to the LinkedList to delete the data from
//i : the data will be deleted from the ith element of the list
//returns : a  status code as defined in linklist.h
int deleteElementI(LinkedList* l, int i){
	ListElement* toDelete = iterate(l,i);
	if(toDelete==NULL) return LLOVERRUN;
	if(toDelete->prevElement==NULL) l->begining = toDelete->nextElement;
	if(toDelete->nextElement==NULL) l->end = toDelete->prevElement;

	return deleteElement(toDelete);
}

//deleteLastElement() removes the last element of the list
//l : a pointer to the LinkedList to delete the data from
//returns : a  status code as defined in linklist.h
int deleteLastElement(LinkedList* l) {
	ListElement* toDelete = l->end;
	if(toDelete == NULL) return LLOVERRUN;
	l->end = l->end->prevElement;
	if(l->end!=NULL) l->end->nextElement = NULL;
	if(l->end==NULL) l->begining = NULL;
	
	return deleteElement(toDelete);;
} 

//deleteFirstElement() removes the first element of the list
//l : a pointer to the LinkedList to delete the data from
//returns : a  status code as defined in linklist.h
int deleteFirstElement(LinkedList* l) {
	ListElement* toDelete = l->begining;
	if(toDelete == NULL) return LLUNDERRUN;
	l->begining = toDelete->nextElement;
	if(l->begining!=NULL) l->begining->prevElement = NULL;
	if(l->begining==NULL) l->end = NULL;
	
	return deleteElement(toDelete);
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
//			not implemented yet.  always returns LLFAIL if called
int sortList(LinkedList* l){
	return LLFAIL;
}



//we could speed up sequential reads by having an iterator datatype
//which would be created by the user but used as a pointer to the
//current location in the array, like a bookmark.  wrap it in a struct to prevent
//tampering.
//should it have an index? should the index be absolute or relative
//how should it handle list deletes?
//LLIterator initLLIterator(LinkedList* l);
//int IterateForward(LLIterator* iterator, void* data);
//int IterateBackward(LLIterator* iterator, void* data);
//int IterateDelete(LLIterator* iterator);

struct LLIterator {
	ListElement* marker;
	LinkedList* list;
};

LLIterator initLLIterator(LinkedList* l){
	LLIterator newIterator;
	newIterator.marker = l->begining;
	newIterator.list = l;
	return newIterator;
}

int IterateForward(LLIterator* iterator, void* data){
	readElement(iterator->marker, data, iterator->list->elementSize);
	if(iterator->marker->nextElement==NULL) return LLOVERRUN;
	else iterator->marker = iterator->marker->nextElement;
	return LLSUCCESS;
}

int IterateBackward(LLIterator* iterator, void* data){
	readElement(iterator->marker, data, iterator->list->elementSize);
	if(iterator->marker->prevElement==NULL) return LLUNDERRUN;
	else iterator->marker = iterator->marker->prevElement;
	return LLSUCCESS;
}

int IterateRead(LLIterator* iterator, void* data){
	return readElement(iterator->marker, data, iterator->list->elementSize);
}

int IterateDelete(LLIterator* iterator){
	if(iterator==NULL) return LLFAIL;
	if(iterator->marker==NULL) return LLFAIL;

	ListElement* newNextElement= iterator->marker->nextElement;

	if(iterator->marker==iterator->list->begining){
		iterator->list->begining = newNextElement;
	}
	if(iterator->marker==iterator->list->end){
		newNextElement = iterator->marker->prevElement;
		iterator->list->end = newNextElement;
	}

	iterator->marker = newNextElement;

	return deleteElement(iterator->marker);

}
