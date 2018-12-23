#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
  int child_pid = fork();

  if (child_pid < 0) {
    fprintf(stderr, "Fork failed\n");

  } else if (child_pid == 0) {

    printf("child pid: (%d)\n", (int) getpid());

    char** exec_arguments;
    exec_arguments[0] = strdup("ls .");
    exec_arguments[1] = strdup("-la");
    exec_arguments[2] = strdup(NULL);

    execvp(exec_arguments[0], exec_arguments);
    printf("Thing that will never get printed\n");
  } else {
    printf("parent pid: (%d)", (int) getpid());
    wait(NULL);
  }

  return 0;
}