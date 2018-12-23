#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
  int fd = open("/tmp/question2_temp_file", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);

  int rc = fork();

  if (rc < 0) {
    fprintf(stderr, "errror forking\n");
  } else if (rc == 0) {
    printf("Im child\n");
    write(fd, "Hello world\n", 13);
  } else {
    printf("Im parent \n");
    write(fd, "Bye world\n", 11);
  }
  return 0;
}

// Both processes can access fd
// The file are shared accross the processes so if one process changes
// it the other will change it too. So files are shared
// To make things more deterministic it'd be better to modify the file
// after the child process is done.