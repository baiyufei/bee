#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define file "/tmp/shared-memory-file"
#define SHARED_SIZE 1024

int main(int argc, char **argv) {
  int fd;
  char *p;

  // set file size
  fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00777);
  lseek(fd, SHARED_SIZE, SEEK_SET);
  write(fd, "", 1);

  p = (char *) mmap(NULL, SHARED_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  close(fd);
  char info[] = "hello world!\n";
  memcpy(p, info, sizeof(info));
  printf("write 'hello world' to shared memory\n");
  sleep(10);
  munmap(p, SHARED_SIZE);
  printf("shared memory write to file\n");
}