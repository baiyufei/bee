#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/file.h>

#define file "/tmp/shared-memory-file-123"
#define SHARED_SIZE 1024

int main(int argc, char **argv) {
  int fd;
  char *p;


  int fd2 = open("/tmp/lll", O_CREAT | O_RDWR);
  printf("file open fd : %d\n", fd2);
  int ret2 = flock(fd2, LOCK_EX);
  printf("ret2 %d\n", ret2);
  perror("");
  flock(fd2, LOCK_UN);
  close(fd2);
  unlink("/tmp/lll");


  // set file size
  fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 00777);
  lseek(fd, SHARED_SIZE, SEEK_SET);
  write(fd, "", 1);

  p = (char *) mmap(NULL, SHARED_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  char info[] = "hello world!\n";
  int ret = flock(fd, LOCK_EX);
  printf("lock %d\n", ret);
  perror("");
  memcpy(p, info, sizeof(info));
  printf("write 'hello world' to shared memory\n");
  sleep(20);
  munmap(p, SHARED_SIZE);
  printf("unlock\n");
  flock(fd, LOCK_UN);
  printf("shared memory write to file\n");
}