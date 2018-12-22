#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "./code.intro/common.h"

int main(int argc, char **argv) {
	// what does it really mean *p. What is p?
	// p is the pointer without a doubt
	int* p = malloc(sizeof(int));
	assert(p != NULL);
	// %p pointers
	// %d decimal / can be use when priting integers
	printf("%d address pointed to by p: %p/n", getpid(), p);

	// we are assigning the dereferenced value meaning the value
	// p is pointing to. So this is not pointer arithmetic
	// getpid() gets the current process id
	// running different instance of this script will produce different pid
	*p = 0;

	while(1) {
		Spin(1);
		*p = *p + 1;
		printf("%d p: %d \n", getpid(), *p);
	}

	return 0;
}