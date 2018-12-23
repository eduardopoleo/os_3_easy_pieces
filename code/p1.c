#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  printf("hello world (pid: %d)\n", (int) getpid());
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed \n");
  } else if (rc == 0) {
    printf("hello, I ma child (pid: %d\n", (int) getpid());
  } else {
    printf("hello, I am parent of %d (pid: %d) \n", rc, (int) getpid());
  }
  return 0;
}