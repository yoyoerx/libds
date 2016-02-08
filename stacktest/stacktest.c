#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "../stack.h"
#include "../utils.h"

#define BUFMAX 100

void pp(){
	printf(".");
}

int main(){
	int i =0;
	
	Stack* intstack;
	Stack* intstack2;
	int inputint = 0;
	int result = 0;
	int m=0;
	int kill;
	scanf("%d", &inputint);
	seed = inputint;
	
	do{
		m++;
		i=0;
		kill = PMrand() % 5000;
		//printf("kill1: %d", kill);
		
		intstack = makeStack(sizeof(int));
		intstack2 = makeStack(sizeof(int));
		
		//dump(intstack, STACKSIZE);
		//dump(intstack2, STACKSIZE);
		//printf("filling the stack...\n");
		
		do{
			i++;
			inputint = PMrand();
			if(rand()%2) pushStack(intstack, &inputint);
			if(rand()%2) pushStack(intstack2, &inputint);
			//pp();
			/*if(!bottom(intstack) && i%5 == 0){
				//pop(intstack, &result);	
				//printf("%d: %d ", i, result);
			}*/
		} while (i<kill);
		
		
		//dump(intstack, STACKSIZE);
		//dump(intstack2, STACKSIZE);
		sleep(1);
		//printf("emptying the stack...\n");
		
		i=0;
		kill = PMrand() % 5000;
		//printf("kill2: %d", kill);
		do{
			i++;
			//dump(intstack, STACKSIZE);
			popStack(intstack, &result);
			popStack(intstack2, &result);
			//printf(" %d", result);
			//pp();
		} while(i<kill);
		
		breakStack(intstack);
		breakStack(intstack2);
		
		sleep(1);
	} while(m<10);
	
	printMemStats();
	
	
	return 0;
}
