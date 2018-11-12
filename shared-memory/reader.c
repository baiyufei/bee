/*-------------map_normalfile2.c-----------*/
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define file "/tmp/shared-memory-file"
#define SHARED_SIZE 1024

int main(int argc, char** argv)  // map a normal file as shared mem:
{
  int fd,i;
  char *p;
  fd=open( file, O_CREAT|O_RDWR, 00777 );
  p = (char*)mmap(NULL, SHARED_SIZE ,PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);
  for(i = 0;i<13;i++)
  {
    putchar(p[i]);
  }
  munmap( p,SHARED_SIZE );
}
