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
int breakList(LinkedList* list);

int addElementI(LinkedList* list, const void* data, int i);
int addLastElement(LinkedList* list, const void* data);
int addFirstElement(LinkedList* list, const void* data);

int readElementI(LinkedList* list, void* data, int i);
int readLastElement(LinkedList* list, void* data);
int readFirstElement(LinkedList* list, void* data);

int deleteElementI(LinkedList* list, int i);
int deleteLastElement(LinkedList* list);
int deleteFirstElement(LinkedList* list);

int isEmpty(LinkedList* list);

//List Iterator Datatype
typedef struct LLIterator LLIterator;

LLIterator* initLLIterator(LinkedList* list);
int breakLLIterator(LLIterator* iterator);
int IterateSetFront(LLIterator* iterator);
int IterateSetBack(LLIterator* iterator);
int IterateForward(LLIterator* iterator);
int IterateBackward(LLIterator* iterator);
int IterateRead(LLIterator* iterator, void* data);
int IterateDelete(LLIterator* iterator);
int IterateInsertBefore(LLIterator* iterator, const void* data);
int IterateInsertAfter(LLIterator* iterator, const void* data);
int IterateSwap(LLIterator* iteratorA, LLIterator* iteratorB);

//Sort Implimentations
int sortList(LinkedList* list);
typedef int (*LinkedListComparator)(const void* element1, const void* element2);
int sortListUserFunction(LinkedList* list, LinkedListComparator compare);

#endif
