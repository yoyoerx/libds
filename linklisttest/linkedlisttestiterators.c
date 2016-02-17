#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../linklist.h"
#include "../utils.h"

#define BUFMAX 100

void pp(){
	printf(".");
}

void pn(){
	printf("\n");
}

int main(){
	int i =0;

	int testData[] = {10, 1, 2 , 3 ,4 ,5 ,6, 7, 8, 9, 10, 11, 12 , 13, 7,1,9,2,2,4,1,3,2,3,6,5,1}; //13 elements
	
	LinkedList* intList;
	int inputint = 0;
	int result = 0;
	int kill = 27;

	int statusCode = LLSUCCESS;
	
	//scanf("%d", &inputint);
	//seed = inputint;
	
	intList = makeList(sizeof(int));
	
	
	printf("\nfilling the list...\n");
	
	do{
		
		
		//inputint = PMrand();
		inputint = testData[i];

		printf("%d", inputint);

		addLastElement(intList, &inputint);
		
		pp();
		i++;
	} while (i<kill);
	
	printf("\nreading the list...\n");

	
	LLIterator* listerater =  initLLIterator(intList);


	printf("\nreading the list from element 1...\n");
	IterateForward(listerater);
	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\nreading the list from element 0...\n");
	IterateSetFront(listerater);
	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\ndelete element 2 and read the list from the front...\n");
	IterateSetFront(listerater);
	IterateForward(listerater);
	IterateForward(listerater);
	IterateDelete(listerater);

	IterateSetFront(listerater);
	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\nreading the 2nd and 3rd to last elements in the list...\n");
	statusCode = IterateBackward(listerater);
	IterateRead(listerater, &result);
	printf("%d %d\n", statusCode, result);

	statusCode = IterateBackward(listerater);
	IterateRead(listerater, &result);
	printf("%d %d\n", statusCode, result);

	printf("\ndelete the 2nd to last ement in the list and read backwards...\n");
	IterateDelete(listerater);

	IterateSetBack(listerater);
	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateBackward(listerater)==LLSUCCESS);
	pn();

	printf("\nread the list forward, delete the last element, read forward again...\n");
	IterateSetFront(listerater);
	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	IterateSetBack(listerater);
	IterateDelete(listerater);

	IterateSetFront(listerater);

	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\ndelete the first element, read forward...\n");
	
	IterateSetFront(listerater);
	IterateDelete(listerater);

	IterateSetFront(listerater);

	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();



	printf("\ndelete the list iterater...\n");

	breakLLIterator(listerater);

	printf("\nbreaking the list...\n");
	breakList(intList);
	printMemStats();
	
	
	return 0;
}
