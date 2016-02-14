#ifndef LINKLIST_H
#define LINKLIST_H


//Linked List status codes
#define LLSUCCESS 0
#define LLUNDERRUN 1
#define LLOVERRUN 3
#define LLFAIL 255

//The linked list data structure
typedef struct LinkedList LinkedList;

//makeList() initalizes a LinkedList
//size : the size of the elements which will go in the list
//			this is user supplied and is assumed to be correct
//returns : a pointer to a LinkedList with 0 elements
//			fails fatally if it cannot allocate memory
LinkedList* makeList(size_t size);

int breakList(LinkedList* l);

int addElement(LinkedList* l, void* data);
int insertElement(LinkedList* l, void* data, int i);

int readElement(LinkedList* l, void* data, int i);
int readLastElement(LinkedList* l, void* data);
int readFirstElement(LinkedList* l, void* data);

int deleteElement(LinkedList* l, int i);
int deleteLastElement(LinkedList* l);
int deleteFirstElement(LinkedList* l);


int isEmpty(LinkedList* l);

int sortList(LinkedList* l);

#endif
