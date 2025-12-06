#include <stdio.h>
#include "pipe_utils.h"

int main() {
  char line[MAX_LINE];

  printf("Enter a pipeline (cmd1 | cmd2): ");
  fgets(line, sizeof(line), stdin);

  // Split into two commands around '|'
  char *cmd1_str = strtok(line, "|");
  char *cmd2_str = strtok(NULL, "|");

  if (!cmd1_str || !cmd2_str) {
    fprintf(stderr, "Error: must contain a pipe, like: ls -l | grep txt\n");
    return 1;
  }

  // Trim whitespace
  while (*cmd1_str == ' ') cmd1_str++;
  while (*cmd2_str == ' ') cmd2_str++;

  // Token arrays
  char *cmd1[MAX_ARGS];
  char *cmd2[MAX_ARGS];

  parse_command(cmd1_str, cmd1);
  parse_command(cmd2_str, cmd2);

  run_pipeline(cmd1, cmd2);
  return 0;
}  
