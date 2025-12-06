#include <stdio.h>
#include <string.h>
#include "pipe_utils.h"

#define MAX_LINE 1024
#define MAX_ARGS 100

void parse_command(char *cmd, char **argv) {
  int i = 0;
  char *token = strtok(cmd, " \t\n");
  while (token != NULL && i < MAX_ARGS - 1) {
    argv[i++] = token;
    token = strtok(NULL, " \t\n");
  }
  argv[i] = NULL;
}

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
