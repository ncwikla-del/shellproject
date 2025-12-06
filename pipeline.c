#include <stdio.h>
#include "pipe_utils.h"

int main() {
  // Example: ls -l | grep .c

  char *cmd1[] = {"ls", "-l", NULL};
  char *cmd2[] = {"grep", ".c", NULL};

  printf("Running: ls -l | grep .c\n");
  run_pipeline(cmd1, cmd2);

  return 0;
}  
