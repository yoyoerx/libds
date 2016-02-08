#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "utils.h"

typedef struct StackElement {
	void *value;
	void *prevelement;
} StackElement;

struct Stack{
	StackElement* top;
	size_t size;
};

Stack* makeStack(size_t size){
	Stack* newStack = ec_malloc(sizeof(Stack));
	newStack->size=size;
	newStack->top = NULL;
	return newStack;
}

int breakStack(Stack* s){
	// this needs to free the stack all the way to the bottom.
	StackElement* holder;
	while (bottomStack(s)==STACKSUCCESS){
		holder = s->top->prevelement;
		ec_free(s->top->value);
		ec_free(s->top);
		s->top = holder;	
	}
	ec_free(s);
	return STACKSUCCESS;
}

int pushStack(Stack* s, void* data){
	StackElement* newElement = ec_malloc(sizeof(StackElement));
	
	newElement->value = ec_malloc(s->size);
	bcopy(data, newElement->value, s->size);
	
	newElement->prevelement = s->top;
	s->top = newElement;
	
	return STACKSUCCESS;
}

int popStack(Stack* s, void* data){
	if(bottomStack(s) == STACKUNDERRUN) return STACKUNDERRUN;
	
	bcopy(s->top->value, data, s->size);
	
	ec_free(s->top->value);
	StackElement* holder = s->top->prevelement;
	ec_free(s->top);
	s->top = holder;
	return STACKSUCCESS;
}

int peekStack(Stack* s,  void* data) {
	if(bottomStack(s) == STACKUNDERRUN) return STACKUNDERRUN;
	bcopy(s->top->value, data, s->size);
	return STACKSUCCESS;
} 

int bottomStack(Stack* s) {
	if(s->top == NULL) return STACKUNDERRUN;
	else return STACKSUCCESS;
} 

