#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
  printf("hello world (pid:%d) \n", (int) getpid());
  // rc is the pid of the new process that just got created from
  // the fork call
  int rc = fork();

  if (rc < 0) {
    printf(stderr, "fork has failed\n");
  } else if (rc == 0) {
    printf("Hey I'm a child process with %d \n", (int) getpid());
  } else {
    // makes the parent process wait until the child finishes!
    // then we are sure that whatever we do here happens after child
    // took care of his bussiness
    int rc_wait = wait(NULL);
    printf("hello, I am a parent of %d (rc_wait: %d) (pid: %d) \n", 
      rc, rc_wait, (int) getpid());
  }

  return 0;
}