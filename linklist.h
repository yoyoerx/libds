#ifndef LINKLIST_H
#define LINKLIST_H


//Linked List status codes
#define LLSUCCESS 0
#define LLUNDERRUN 1
#define LLOVERRUN 3
#define LLFAIL 255

//The linked list data structure
typedef struct LinkedList LinkedList;


LinkedList* makeList(size_t size);

int breakList(LinkedList* l);

int addElement(LinkedList* l, void* data);
int insertElement(LinkedList* l, void* data, int i);

int readElementI(LinkedList* l, void* data, int i);
int readLastElement(LinkedList* l, void* data);
int readFirstElement(LinkedList* l, void* data);

int deleteElementI(LinkedList* l, int i);
int deleteLastElement(LinkedList* l);
int deleteFirstElement(LinkedList* l);


int isEmpty(LinkedList* l);

int sortList(LinkedList* l);

//List Iterator Datatype
typedef struct LLIterator LLIterator;
LLIterator initLLIterator(LinkedList* l);
int IterateForward(LLIterator* iterator, void* data);
int IterateBackward(LLIterator* iterator, void* data);
int IterateRead(LLIterator* iterator, void* data);
int IterateDelete(LLIterator* iterator);

#endif
