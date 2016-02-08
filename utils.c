#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"


int malloccount=0;
int calloccount=0;
int freecount=0;

#define a 48271
#define m 2147483647
#define q (m / a)
#define r (m % a)
long int seed=1;

long int PMrand(){
	long int hi = seed / q;
	long int lo = seed % q;
	long int test = a * lo - r * hi;
	if(test > 0)
		seed = test;
	else	seed = test + m;
	return seed;
}

void fatal(char *message) {
   char error_message[100];

   strcpy(error_message, "[!!] Fatal Error ");
   strncat(error_message, message, 83);
   perror(error_message);
   exit(-1);
}

void *ec_malloc(size_t size) {
	void *ptr;
	ptr = malloc(size);
	malloccount++;
	if(ptr == NULL)
		fatal("in ec_malloc() on memory allocation");
	return ptr;
}

void *ec_calloc(size_t nmemb, size_t size) {
	void *ptr;
	ptr = calloc(nmemb, size);
	calloccount++;
	if(ptr == NULL)
		fatal("in ec_calloc() on memory allocation");
	return ptr;
}

void ec_free(void *ptr) {
	if(ptr == NULL)
		fatal("in ec_free() on memory deallocation, freeing NULL pointer");
	free(ptr);
	freecount++;
	ptr = NULL;
	return;
}

void printMemStats(){
	printf("\n\n-------------------MEM-STATS-------------------------\n");
	printf("          malloc calls:   %d            \n", malloccount);
	printf("          calloc calls:   %d            \n", calloccount);
	printf("            free calls:   %d            \n", freecount);
	printf("            leaked mem:   %d            \n", (malloccount+calloccount) - freecount);
	printf("-------------------MEM-STATS-------------------------\n");
}

void dump(const unsigned char *data_buffer, const unsigned int length) {
        unsigned char byte;
        unsigned int i, j;
        for(i=0; i < length; i++) {
                byte = data_buffer[i];
                printf("%02x ", data_buffer[i]);  // Display byte in hex.
                if(((i%16)==15) || (i==length-1)) {
                        for(j=0; j < 15-(i%16); j++)
                                printf("   ");
                        printf("| ");
                        for(j=(i-(i%16)); j <= i; j++) {  // Display printable bytes from line.
                                byte = data_buffer[j];
                                if((byte > 31) && (byte < 127)) // Outside printable char range
                                        printf("%c", byte);
                                else
                                        printf(".");
                        }
                        printf("\n"); // End of the dump line (each line is 16 bytes)
                } // End if
        } // End for
}
