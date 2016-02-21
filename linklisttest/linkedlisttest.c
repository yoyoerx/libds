#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../linklist.h"
#include "../utils.h"

#define BUFMAX 100

static void pp(){
	printf(".");
}

int main(){
	int i =0;

	int testData[] = {0, 1, 2 , 3 ,4 ,5 ,6, 7, 8, 9, 10, 11, 12 , 13, 7,1,9,2,2,4,1,3,2,3,6,5,1}; //13 elements
	
	LinkedList intList;
	int inputint = 0;
	int result = 0;

	int kill = 13;
	
	//scanf("%d", &inputint);
	//seed = inputint;
	
	intList = makeList(sizeof(int));
	
	
	printf("\nfilling the list...\n");
	
	do{
		
		
		//inputint = PMrand();
		inputint = testData[i];

		printf(" %d ", inputint);

		addLastElement(intList, &inputint);
		
		pp();
		i++;
	} while (i<kill);
	
	printf("\nmodifying the list...\n");

	
	
	//read/delete first element
	readFirstElement(intList, &result);
	printf("%d \n", result);
	deleteFirstElement(intList);

	//read/delete last element
	readLastElement(intList, &result);
	printf("%d \n", result);
	deleteLastElement(intList);

	//read/delete 5th element
	readElementI(intList, &result, 5);
	printf("%d \n", result);
	deleteElementI(intList, 5);

	//read/delete 0th element
	readElementI(intList, &result, 0);
	printf("%d \n", result);
	deleteElementI(intList, 0);

	//read/delete element out of bounds
	readElementI(intList, &result, 100);
	printf("%d \n", result);
	deleteElementI(intList, 100);
	
	//sequential read
	i=0;
	while(LLSUCCESS==readElementI(intList, &result, i)){
		printf("%d", result); pp();
		i++;
	}
	


	//test insert element at 5
	result = 77;
	addElementI(intList, &result, 5);
	readElementI(intList, &result, 5);
	printf("\nInserted %d at i=5\n", result);

	//test insert element at 0
	result = 55;
	addElementI(intList, &result, 0);
	readElementI(intList, &result, 0);
	printf("\nInserted %d at i=0\n", result);

	//test insert element out of bounds
	result = 99;
	addElementI(intList, &result, 11);
	readElementI(intList, &result, 11);
	printf("\nInserted %d at i=11\n", result);

	//sequential read
	i=0;
	while(LLSUCCESS==readElementI(intList, &result, i)){
		printf("%d", result);pp();
		i++;
	}
	


	printf("\nemptying the list...\n");

	do{
		readFirstElement(intList, &result);
		printf("%d ", result);
		deleteFirstElement(intList);
	} while(isEmpty(intList)==LLSUCCESS);

	//Test operations on an empty list
	printf("\nempty list test...\n");
	result = -1;
	//read/delete first element
	readFirstElement(intList, &result);
	printf("%d \n", result);
	deleteFirstElement(intList);

	//read/delete last element
	readLastElement(intList, &result);
	printf("%d \n", result);
	deleteLastElement(intList);

	//read/delete 5th element
	readElementI(intList, &result, 5);
	printf("%d \n", result);
	deleteElementI(intList, 5);


	
	printf("\nfilling the list...\n");
	
	i=0;
	do{
		
		inputint = testData[i];
 
		printf(" %d ", inputint);

		addLastElement(intList, &inputint);
		
		pp();
		i++;
	} while (i<kill);

	printf("\nbreaking the list...\n");
	breakList(intList);
	printMemStats();
	
	
	return 0;
}
