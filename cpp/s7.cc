// example of pthread_atfork

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void before() {
  pid_t pid = getpid();
  printf("%d: before fork\n", (int) pid);
}

void father() {
  pid_t pid = getpid();
  printf("%d: after fork father\n", (int) pid);
}

void child() {
  pid_t pid = getpid();
  printf("%d: after fork child\n", (int) pid);
}

int main() {
  pthread_atfork(before, father, child);
  fork();
  
  return 0;
}