#ifndef UTILS_H
#define UTILS_H

int malloccount;
int calloccount;
int freecount;

long int seed;
long int PMrand();

void fatal(char *message);

void *ec_malloc(size_t size);
void *ec_calloc(size_t nmemb, size_t size);
void ec_free(void *ptr);

void printMemStats();

void dump(const unsigned char *data_buffer, const unsigned int length);

#endif
