#ifndef STACK_H
#define STACK_H

#define STACKSUCCESS 0
#define STACKUNDERRUN 1
#define STACKFAIL 255


typedef struct Stack Stack;

Stack* makeStack(size_t size);
int breakStack(Stack* s);
int pushStack(Stack* s, void* data);
int popStack(Stack* s, void* data);
int peekStack(Stack* s,  void* data);
int bottomStack(Stack* s);


#endif
