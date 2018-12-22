#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include <string.h>
#include "./code.intro/common.h"

int main(int argc, char** argv) {
	for (int i = 0; i < argc; i++) {
		// argv is an array of POINTERs therefore extracting elements from it
		// will result in pointers
		char *current_arg = argv[i];

		// strlen gives you the string len when the ref is passed to it
		int arg_size = strlen(current_arg);

		for (int j = 0; j < arg_size; j++) {
			// each current_arg is an array of CHARs therefore extracting elements from it
			// will result on a char
			char current_char = current_arg[j];
			printf("%c ", current_char);
		}

		printf("\n");
	}
	return 0;
}

// for loop 
// initial, rule, increment I;R;I