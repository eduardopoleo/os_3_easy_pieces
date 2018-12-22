#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char** argv) {
	// O_RDWR are file options such as read and write, create if does no exist etc
	// if is the file descriptor. Integer that points to the open file and allows 
	// the os to find it.
	int fd = open("/tmp/file", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	assert(fd > -1);
	// write requires the fd, the buffer to persist and the count of bytes from that 
	// buffer to persist.
	// Why does it create the file on binary
	int rc = write(fd, "Hello world\n", 13);
	assert(rc == 13);
	close(fd);
	return 0;
}