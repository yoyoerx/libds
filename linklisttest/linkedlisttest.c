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

int main(){
	int i =0;
	
	LinkedList* intList;
	int inputint = 0;
	int result = 0;
	int m=0;
	int kill;
	
	//scanf("%d", &inputint);
	//seed = inputint;
	
	intList = makeList(sizeof(int));

	do{
		m++;
		i=0;
		
		//kill = PMrand() % 5000;
		kill = 3;
		
		//intList = makeList(sizeof(int));
		
		printf("filling the list...\n");
		
		do{
			i++;
			
			inputint = PMrand();
			printf("%d\n", inputint);

			addElement(intList, &inputint);
			
			//pp();
			
		} while (i<kill);
		
		//sleep(1);
		printf("emptying the list...\n");
		
		do{
			readFirstElement(intList, &result);
			printf("%d\n", result);
			printf("%d\n", deleteFirstElement(intList));
			printf("%d\n", isEmpty(intList));
			//pp();
		} while(isEmpty(intList)==LLSUCCESS);
		
		
		
		//breakList(intList);
		
		//sleep(1);
	} while(m<10);
	printf("breaking the list...\n");
	breakList(intList);
	printMemStats();
	
	
	return 0;
}
