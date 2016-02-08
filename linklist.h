#ifndef LINKLIST_H
#define LINKLIST_H

#define LLSUCCESS 0
#define LLUNDERRUN 1
#define LLOVERRUN 3
#define LLFAIL 255

typedef struct LinkedList LinkedList;

LinkedList* makeList(size_t size);
int breakList(LinkedList* l);
int addElement(LinkedList* l, void* data);
int insertElement(LinkedList* l, void* data, int i);

int readElement(LinkedList* l, int i);

int deleteElement(LinkedList* l, int i);

int empty(LinkedList* l);

int sortList(LinkedList* l);

#endif
