#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char **argv) {
  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "fork did not work joe\n");
    exit(1);
  } else if (rc == 0) {
    // closes the standard output file so that we do not print 
    // to the console
    close(STDOUT_FILENO);
    // replaces the stdout by this new file 
    open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    // no the exec

    //builds the arguments for the exec

    // equivalent of char **argv I get so confused with this notation
    // because it's almost the same as  char S1[3] which builds a string of 3 chars
    char *myargs[3]; 
    myargs[0] = strdup("wc"); // myargs[0] 
    myargs[1] = strdup("p4.c");
    myargs[2] = NULL;

    // execute the new command
    execvp(myargs[0], myargs);
  } else {
    // the parent waits until the child process finishes 
    int rc_wait = wait(NULL);
  }

  return 0;
}

// This program is the equivalent of > (nice cuz I just used it)

int main(int argc, char const *argv[])
{
  /* code */
  return 0;
}