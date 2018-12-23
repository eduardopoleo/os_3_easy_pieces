#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  printf("hello world (pid: %d) \n", (int) getpid());
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork failed\n");
    exit(1);
  } else if (rc == 0) {
    printf("hello, I am a chile (pid: %d) \n", (int) getpid());

    char *myargs[3]; // creates an array of pointers to char
    myargs[0] = strdup("wc"); // [] auto dereference the pointers 
    myargs[1] = strdup("p3.c");
    myargs[2] = NULL;

    // exec in this case will run wc on p3.c 
    // the code of the child process (which used to be this same p3 process)
    // gets overriden by the wc
    // therefore the last print statement never runs
    execvp(myargs[0], myargs);

    printf("this should not print out\n");
  } else {
    int rc_wait = wait(NULL);
    printf("hello i'm a parent of %d (rc_wait: %d) (pid: %d)\n", rc, rc_wait, (int) getpid());
  }

  return 0;
}