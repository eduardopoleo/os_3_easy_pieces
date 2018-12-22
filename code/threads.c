#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "./code.intro/common.h"

// Prevents variable optimization and caching
// This is useful necessary in this case because 
// the variable counter will be changed by different
// threads
volatile int counter = 0;
int loops;

void* worker(void *args) {
	for (int i = 0; i < loops; i++) {
		counter++;
	}

	return NULL;
}

int main(int argc, char** argv) {

	if (argc != 2) {
		fprintf(stderr, "usage: threads <value> \n");
		exit(1);
	}

	loops = atoi(argv[1]);

	pthread_t p1, p2;

	printf("Inital value: %d\n", counter);
	pthread_create(&p1, NULL, worker, NULL);
	pthread_create(&p2, NULL, worker, NULL);
	// It's confusing that the apis for create takes the 
	// reference while the join takes the actual thread.
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);

	printf("Final value : %d\n", counter);

	return 0;
}