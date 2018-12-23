#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  printf("This is the parent process (pid: %d)\n", (int) getpid());
  int rc;
  int x = 100;

  rc = fork();

  if (rc < 0) {
    fprintf(stderr, "The process fork did not work\n");
  } else if(rc == 0) {
    printf("This is child process (pid: %d) \n", (int) getpid());

    // this prints 100. The stack gets copied identical as the
    // parent. They do not share state (like threads)
    printf("X from within child BEFORE: %d \n", x);
    x = 10;

    // this as expected returns 10
    printf("X from within child AFTER: %d \n", x);
  } else  {
    wait(NULL);

    // This happens after the child return but as expected
    // it's still 100 cuz it's not sharing state with the
    // child process
    printf("X from within parent BEFORE: %d \n", x);
    x = 20;

    // this as expected is 20
    printf("X from within parent AFTER: %d \n", x);

    printf("This is parent again (pid: %d)\n", (int) getpid());
  }

  return 0;
}

// Anwser: Both chile and parent can x
// chaning the value on 1 process does not change it on the other