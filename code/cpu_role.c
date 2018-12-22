#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "./code.intro/common.h"

int main(int argc, char *argv[]) {
	// Assumes only one argument.
	// The first argument is alwasy the name of the script
	if (argc != 2) {
		fprintf(stderr, "usage: cpu <string>\n");
		exit(1);
	}

	char *first_argument = argv[0];
	char *second_argument = argv[1];

	while (1) {
		Spin(1);
		printf("FIRST %s \n", first_argument);
		printf("SECOND %s \n", second_argument);
	}
	return 0;
}

// char *argv[] => char **argv
// this refers to an array of arrays (each string is an array of chars)
// argv keeps track of the position of the first char of every string

// consequently char *first_argument = argv[0] is correct cuz argv[number]
// will be a pointer

// On referencing (FROM value TO pointer)
// int n;
// int *p;
// n = 5
// p = &n; I'm refering or finding the reference of the value

// On derefering (FROM pointer TO value)
// int n1;
// n1 = *p; I'm derefering or finding the value at the reference.

