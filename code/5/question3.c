// The child process should print “hello”;
// the parent process should print “goodbye”. You should try to ensure that
// the child process always prints first; can you do this without calling wait() in
// the parent?

// How can I check the status of a process? 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/time.h>
#include "./code.intro/common.h"

// This solution is not complete. I can't find a reliable way to check for the
// status of a process.
// source http://pubs.opengroup.org/onlinepubs/009695399/functions/waitpid.html

int main(int argc, char const *argv[])
{
  int status;
  int child_pid = fork();

  if (child_pid < 0)
  {
    fprintf(stderr, "Fork failed\n");
  } else if (child_pid == 0)
  {
    printf("At the market\n");
    Spin(10);
  } else {
    int wpid = waitpid(child_pid, &status, WUNTRACED | WCONTINUED);

    // poll for the child status until is done
    while(WIFCONTINUED(status)) {
      printf("waiting...\n");
    }

    printf("Ok my child did came back\n");
  }
  return 0;
}
