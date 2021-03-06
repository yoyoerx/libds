#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "linklist.h"
#include "utils.h"



//ListElement is a struct (this is also a datatype for ease of use) contains
//			implementations of this library should not touch ListElements
// value : a pointer to allocated memory of size LinkedList->elementSize
// prevElement : a pointer to the ListElement directly before IT in the linked list
//                 and is NULL if THIS is the first element in the list
// nextElement : a pointer to the ListElement directly after IT it the linked list
//                 and is NULL if THIS is the last element in the list 
struct ListElement;
typedef struct ListElement ListElement;
struct ListElement {
	void* value;
	ListElement* prevElement;
	ListElement* nextElement;
};

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
//list : a pointer to the LinkedList
//i : an integer number of elements to traverse before returning
//returns : a pointer to the ith ListElement
//			if i<=0, returns list->begining
//			if i>number of elements, returns NULL
static ListElement* iterate(const LinkedList list, int i){
	int n;
	ListElement* holder = NULL;
	
	holder = list->begining;
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
static ListElement* createElement(const void* data, size_t size){
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
//			assumes that data is correctly sized based on list->elementSize
//size : the size of the data element to be read
//returns : a  status code as defined in linklist.h
//			if e==null, data is not changed and returns LLFAIL
static int readElement(const ListElement* e, void* data, size_t size){
	if(e==NULL) return LLFAIL;
	bcopy(e->value, data, size);
	return LLSUCCESS;
}

//deleteElement() deletes an existing ListElement
//toDelete : a pointer to the ListElement to delete
//returns : a  status code as defined in linklist.h
//			fails fatally if pointer toDelete is NULL
static int deleteElement(ListElement* toDelete){

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


//who ever calls swapElements needs to check for and clean up the list
//begining and end pointers. otherwise, segfaults, lost data, and memoryleaks...
static int swapElements(ListElement* elementA, ListElement* elementB){
	if(elementA==NULL||elementB==NULL) return LLFAIL;
	ListElement* prevHolder = elementA->prevElement;
	ListElement* nextHolder = elementA->nextElement;
	elementA->prevElement = elementB->prevElement;
	elementA->nextElement = elementB->nextElement;
	elementB->prevElement = prevHolder;
	elementB->nextElement = nextHolder;

	//set the prevElement's next for both A and B
	if(elementA->prevElement!=NULL) elementA->prevElement->nextElement = elementA;
	if(elementB->prevElement!=NULL) elementB->prevElement->nextElement = elementB;

	//set the nextElement's prev for both A and B
	if(elementA->nextElement!=NULL) elementA->nextElement->prevElement = elementA;
	if(elementA->prevElement!=NULL) elementB->nextElement->prevElement = elementB;



	return LLSUCCESS;
}

//PUBLIC FUNCTIONS//////////////////////////////////////////////////////////////////

//makeList() initalizes a LinkedList
//size : the size of the elements which will go in the list
//			this is user supplied and is assumed to be correct
//returns : a pointer to a LinkedList with 0 elements
//			fails fatally if it cannot allocate memory
LinkedList makeList(size_t size){
	LinkedList newList = ec_malloc(sizeof(LinkedList));
	newList->elementSize=size;
	newList->begining = NULL;
	newList->end = NULL;
	return newList;
}

//breakList() deallocates all memory used in a LinkedList
//list : a pointer to the LinkedList to be deallocated
//returns : a status code as defined in linklist.h
int breakList(LinkedList list){
	while(isEmpty(list)==LLSUCCESS){
		deleteLastElement(list);
	}
	ec_free(list);
	return LLSUCCESS;
}

//addElementI() adds data at an arbitraty location, i, in the list
//list : a pointer to the LinkedList to add the data to
//data : a pointer to the data to be added
//			assumes that data is correctly sized based on list->elementSize
//i : the data added becomes the ith ListElement
// 			if i>number of elements, returns LLOVERRUN
//			if i<=0, element is inserted at the begining of the list
//returns : a  status code as defined in linklist.h
int addElementI(LinkedList list, const void* data, int i){
	
	ListElement* oldIthElement = iterate(list, i);
	if(oldIthElement==NULL) {
		oldIthElement = iterate(list,i-1);
		if(oldIthElement==NULL) return LLOVERRUN;
		//case for inserting at end of list
		return addLastElement(list, data);
	}
		
	ListElement* newElement = createElement(data, list->elementSize);

	newElement->prevElement = oldIthElement->prevElement;
	newElement->nextElement = oldIthElement;
	oldIthElement->prevElement = newElement;

	if(newElement->prevElement==NULL) list->begining = newElement;
	else{
		ListElement* beforeInsert = newElement->prevElement;
		beforeInsert->nextElement = newElement;
	}

	return LLSUCCESS;
}

//addLastElement() adds data to the end of the list
//list : a pointer to the LinkedList to add the data to
//data : a pointer to the data to be added
//			assumes that data is correctly sized based on list->elementSize
//returns : a  status code as defined in linklist.h
int addLastElement(LinkedList list, const void* data){
	ListElement* newElement = createElement(data, list->elementSize);

	newElement->nextElement = NULL;
	newElement->prevElement = list->end;
	if(list->end!=NULL) list->end->nextElement = newElement;
	list->end = newElement;
	
	if(list->begining == NULL){
		list->begining = list->end;
	}
	return LLSUCCESS;
}

//addFirstElement() adds data to the begining of the list
//list : a pointer to the LinkedList to add the data to
//data : a pointer to the data to be added
//			assumes that data is correctly sized based on list->elementSize
//returns : a  status code as defined in linklist.h
int addFirstElement(LinkedList list, const void* data){
	ListElement* newElement = createElement(data, list->elementSize);

	newElement->prevElement = NULL;
	newElement->nextElement = list->begining;
	if(list->begining!=NULL) list->begining->nextElement = newElement;
	list->begining = newElement;
	
	if(list->end == NULL){
		list->end= list->begining;
	}
	return LLSUCCESS;
}

//readElementI() provides a copy of the data in ListElement i
//list : a pointer to the LinkedList to read the data from
//data : a pointer to memory allocated to accept the data from the list
//			assumes that data is correctly sized based on list->elementSize
//i : the data will be read from the ith element of the list
//returns : a  status code as defined in linklist.h
//			if i>number of elements, data is not changed and returns LLUNDERRUN
int readElementI(const LinkedList list, void* data, int i){
	ListElement* toRead = iterate(list,i);
	if(readElement(toRead, data, list->elementSize)==LLFAIL) return LLOVERRUN;
	return LLSUCCESS;
}

int readLastElement(const LinkedList list, void* data){
	ListElement* toRead = list->end;
	if(readElement(toRead, data, list->elementSize)==LLFAIL) return LLOVERRUN;
	return LLSUCCESS;
}

int readFirstElement(const LinkedList list, void* data){
	ListElement* toRead = list->begining;
	if(readElement(toRead, data, list->elementSize)==LLFAIL) return LLUNDERRUN;
	return LLSUCCESS;
}

//deleteElementI() removes the ith element of the list
//list : a pointer to the LinkedList to delete the data from
//i : the data will be deleted from the ith element of the list
//returns : a  status code as defined in linklist.h
int deleteElementI(LinkedList list, int i){
	ListElement* toDelete = iterate(list,i);
	if(toDelete==NULL) return LLOVERRUN;
	if(toDelete->prevElement==NULL) list->begining = toDelete->nextElement;
	if(toDelete->nextElement==NULL) list->end = toDelete->prevElement;

	return deleteElement(toDelete);
}

//deleteLastElement() removes the last element of the list
//list : a pointer to the LinkedList to delete the data from
//returns : a  status code as defined in linklist.h
int deleteLastElement(LinkedList list) {
	ListElement* toDelete = list->end;
	if(toDelete == NULL) return LLOVERRUN;
	list->end = list->end->prevElement;
	if(list->end!=NULL) list->end->nextElement = NULL;
	if(list->end==NULL) list->begining = NULL;
	
	return deleteElement(toDelete);;
} 

//deleteFirstElement() removes the first element of the list
//list : a pointer to the LinkedList to delete the data from
//returns : a  status code as defined in linklist.h
int deleteFirstElement(LinkedList list) {
	ListElement* toDelete = list->begining;
	if(toDelete == NULL) return LLUNDERRUN;
	list->begining = toDelete->nextElement;
	if(list->begining!=NULL) list->begining->prevElement = NULL;
	if(list->begining==NULL) list->end = NULL;
	
	return deleteElement(toDelete);
} 

//isEmpty() determines if the list is empty or not
//list : a pointer to the LinkedList to check
//returns : LLSUCCESS if list still has elements
//			or LLUNDERRUN if list is empty
int isEmpty(const LinkedList list){
	if(list->begining == NULL) return LLUNDERRUN;
	else return LLSUCCESS;
}

//Iterator system to speed up sequential reads
//The iterator itself has a pointer to the LinkedList it serves.
struct LLIterator {
	ListElement* marker;
	LinkedList list;
};

LLIterator initLLIterator(const LinkedList list){
	LLIterator newIterator = ec_malloc(sizeof(LLIterator));;
	newIterator->marker = list->begining;
	newIterator->list = list;
	return newIterator;
}

int breakLLIterator(LLIterator iterator){
	ec_free(iterator);
	iterator = NULL;
	return LLSUCCESS;
}

int IterateSetFront(LLIterator iterator){
	iterator->marker = iterator->list->begining;
	if(iterator->marker==NULL) return LLUNDERRUN;
	return LLSUCCESS;
}

int IterateSetBack(LLIterator iterator){
	iterator->marker = iterator->list->end;
	if(iterator->marker==NULL) return LLUNDERRUN;
	return LLSUCCESS;
}

int IterateForward(LLIterator iterator){
	if(iterator->marker->nextElement==NULL) return LLOVERRUN;
	else iterator->marker = iterator->marker->nextElement;
	return LLSUCCESS;
}

int IterateBackward(LLIterator iterator){
	if(iterator->marker->prevElement==NULL) return LLUNDERRUN;
	else iterator->marker = iterator->marker->prevElement;
	return LLSUCCESS;
}

int IterateRead(const LLIterator iterator, void* data){
	if(iterator->marker==NULL) return LLUNDERRUN;
	return readElement(iterator->marker, data, iterator->list->elementSize);
}

int IterateDelete(LLIterator iterator){
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

	ListElement* toDelete = iterator->marker;
	iterator->marker = newNextElement;

	return deleteElement(toDelete);

}

int IterateInsertBefore(LLIterator iterator, const void* data){
	ListElement* newElement = createElement(data, iterator->list->elementSize);
	newElement->prevElement = iterator->marker->prevElement;
	iterator->marker->prevElement = newElement;
	newElement->nextElement = iterator->marker;
	if(newElement->prevElement!=NULL) 
		newElement->prevElement->nextElement = newElement;
	else
		iterator->list->begining = newElement;

	return LLSUCCESS;
}
int IterateInsertAfter(LLIterator iterator, const void* data){
	ListElement* newElement = createElement(data, iterator->list->elementSize);
	newElement->nextElement = iterator->marker->nextElement;
	iterator->marker->nextElement = newElement;
	newElement->prevElement = iterator->marker;
	if(newElement->nextElement!=NULL) 
		newElement->nextElement->prevElement = newElement;
	else
		iterator->list->end = newElement;

	return LLSUCCESS;
}

//IterateSwap() exchanges the position of two elements from the _same list_
//the iterators continue to point to the same memory addresses, but thier
//position in the list is changed. e.g. iteratorA points to 5 at position 3
//& iteratorB points to 10 at position 7. after the swap, iteratorA will point
//to 5 at position 7 and iteratorB will point to 10 at position 3.
//iteratorA : an LLIterator to the first value to swap
//iteratorB : an LLIterator to the second value to swap
//returns : a status code as defined in linklist.h
//			if iterators are not from the same list, they are not exchanged
//			and returns LLFAIL
//			if either iterator has a NULL element, they elements are not
//			exchanged, and returns LLFAIL
int IterateSwap(LLIterator iteratorA, LLIterator iteratorB){

	if(iteratorA->list!=iteratorB->list) return LLFAIL;
	int retval = swapElements(iteratorA->marker, iteratorB->marker);

	//if the elements we are swaping are at the begining or end of the list,
	//then we need to adjust the pointers in the list appropriatly
	if(retval==LLSUCCESS){
		if(iteratorA->list->begining == iteratorA->marker){
			iteratorA->list->begining = iteratorB->marker;
		} else if(iteratorA->list->begining == iteratorB->marker){
			iteratorA->list->begining = iteratorA->marker;
		}
		if(iteratorA->list->end == iteratorA->marker){
			iteratorA->list->end = iteratorB->marker;
		} else if(iteratorA->list->end == iteratorB->marker){
			iteratorA->list->end = iteratorA->marker;
		}
	}
	return retval;
}

//sortList() puts the list in increasing order based on the > operator
//			if the data is not suitable for sorting in this way,
//			do not use this method if your data cannot be sorted this way
//list : a pointer to the LinkedList to sort
//returns : a  status code as defined in linklist.h
//			not implemented yet.  always returns LLFAIL if called
int sortList(LinkedList list){
	return LLFAIL;
}

//sort list based on user supplied function
int sortListUserFunction(LinkedList list, LinkedListComparator compare){
	return LLFAIL;
}

/*
//debugging functions
void printListElement(ListElement* element){
	printf("Printing ListElement 0x%08X:\n", element);
	printf("{      value = 0x%08X}\n", element->value);
	printf("{prevElement = 0x%08X}\n", element->prevElement);
	printf("{nextElement = 0x%08X}\n", element->nextElement);
}


void printLinkedList(LinkedList list, uint8_t printelement){
	printf("Printing LinkedList 0x%08X:\n", list);
	printf("{   begining = 0x%08X}\n", list->begining);
	printf("{        end = 0x%08X}\n", list->end);
	printf("{elementSize = 0x%08d}\n", list->elementSize);
	if(printelement){
		printf("ListElement at begining:\n");
		printListElement(list->begining);
		printf("ListElement at end:\n");
		printListElement(list->end);
	}

}

void printLLIterator(LLIterator iterator, uint8_t printmarker, uint8_t printlist, uint8_t printelement){
	printf("Printing LLIterator 0x%08X:\n", iterator);
	printf("{     marker = 0x%08X}\n", iterator->marker);
	printf("{       list = 0x%08X}\n", iterator->list);
	if(printmarker){
		printf("ListElement at marker:\n");
		printListElement(iterator->marker);
	}
	if(printlist){
		printf("LinkedList at list:\n");
		printLinkedList(iterator->list, printelement);	
	}	
}
*/
