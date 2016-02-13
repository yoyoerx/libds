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
	
	do{
		m++;
		i=0;
		
		//kill = PMrand() % 5000;
		kill = 20;
		
		intList = makeList(sizeof(int));
		
		printf("filling the list...\n");
		
		do{
			i++;
			
			inputint = PMrand();
			
			addElement(intList, &inputint);
			
			//pp();
			
		} while (i<kill);
		
		//sleep(1);
		printf("emptying the list...\n");
		
		do{

			deleteLastElement(intList);
			//pp();
		} while(isEmpty(intList)==LLSUCCESS);
		
		printf("breaking the list...\n");
		
		breakList(intList);
		
		//sleep(1);
	} while(m<10);
	
	printMemStats();
	
	
	return 0;
}
