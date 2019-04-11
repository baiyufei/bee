#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getVirtMemoryKb(int* currVirtMem) {
  // stores each word in status file
  char buffer[1024] = "";

  // linux file contains this-process info
  FILE* file = fopen("/proc/self/status", "r");

  // read the entire file
  while (fscanf(file, " %1023s", buffer) == 1) {
    if (strcmp(buffer, "VmSize:") == 0) {
      fscanf(file, " %d", currVirtMem);
      break;
    }
  }
  fclose(file);
}
