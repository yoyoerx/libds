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

	int testData[] = {42, 1, 2 , 3 ,4 ,5 ,6, 7, 8, 9, 10, 11, 12 , 13, 14,15,16,17,18,19,1,3,2,3,6,5,1}; //13 elements
	
	LinkedList intList;
	int inputint = 0;
	int result = 0;
	int kill = 20;

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

	
	LLIterator listerater =  initLLIterator(intList);


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

	printf("\nswap the 3rd and 2nd to last element, read forward...\n");
	LLIterator listerater2 = initLLIterator(intList);

	IterateSetFront(listerater);
	IterateForward(listerater);
	IterateForward(listerater);
	IterateSetBack(listerater2);
	IterateBackward(listerater2);

	IterateSwap(listerater, listerater2);

	IterateSetFront(listerater2);


	do{
		IterateRead(listerater2, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater2)==LLSUCCESS);
	pn();

	printf("\nswap the 1st and last element, read forward...\n");
	
	IterateSetFront(listerater);
	IterateSetBack(listerater2);

	IterateSwap(listerater, listerater2);

	IterateSetFront(listerater);

	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\nswap the 1st and last element, read forward...\n");
	
	IterateSetFront(listerater);
	IterateSetBack(listerater2);

	IterateSwap(listerater2, listerater); //make sure it works in either order

	IterateSetFront(listerater);

	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\ninsert 5000 after front then insert 4000 before front, read forward...\n");
	
	IterateSetFront(listerater);
	inputint = 5000;
	IterateInsertAfter(listerater, &inputint);
	inputint = 4000;
	IterateInsertBefore(listerater, &inputint);

	IterateSetFront(listerater);

	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\ninsert 3000 before back then insert 2000 after back, read forward...\n");
	
	IterateSetBack(listerater);
	inputint = 3000;
	IterateInsertBefore(listerater, &inputint);
	inputint = 2000;
	IterateInsertAfter(listerater, &inputint);

	IterateSetFront(listerater);

	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateForward(listerater)==LLSUCCESS);
	pn();

	printf("\nread backwards...\n");

	IterateSetBack(listerater);
	do{
		IterateRead(listerater, &result);
		printf("%d", result); pp();
	}while(IterateBackward(listerater)==LLSUCCESS);
	pn();

	printf("\ndelete the list iterater...\n");

	breakLLIterator(listerater);
	breakLLIterator(listerater2);

	printf("\nbreaking the list...\n");
	breakList(intList);
	printMemStats();
	
	
	return 0;
}
