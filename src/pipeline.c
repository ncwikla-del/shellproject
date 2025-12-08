#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pipe_utils.h"

#define MAX_LINE 2048

// Helper to trim leading and trailing whitespace
void trim(char **str) {
  while (**str == ' ' || **str == '\t') (*str)++;
  char *end = *str + strlen(*str) - 1;
  while (end > *str && (*end == ' ' || *end == '\t' || *end == '\n')) {
     *end = '\0';
     end--;
  }
}

int main() {
  char line[MAX_LINE];

  printf("Enter a pipeline (cmd1 | cmd2 | ...): ");
  if (!fgets(line, sizeof(line), stdin)) {
    fprintf(stderr, "Error reading input\n");
    return 1;
  }

  char *cmd_strings[MAX_CMDS];
  int num_cmds = 0;

  // Split around '|'
  char *token = strtok(line, "|");
  while (token != NULL && num_cmds < MAX_CMDS) {
    trim(&token);
    if (strlen(token) > 0) {
      cmd_strings[num_cmds++] = token;
    }
    token = strtok(NULL, "|");
  }

  if (num_cmds == 0) {
    fprintf(stderr, "Error: no commands entered\n");
    return 1;
  }

  // Convert each command string to argv[]
  char *cmds[MAX_CMDS][MAX_ARGS];
  for (int i = 0; i < num_cmds; i++) {
    parse_command(cmd_strings[i], cmds[i]);
  }

  // Run the full pipeline
  return run_pipeline(cmds, num_cmds, NULL, NULL, 0);
}
