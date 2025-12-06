#include "pipe_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void error_and_exit(const char *msg) {
  perror(msg);
  exit(1);
}

int run_pipeline(char *cmd1[], char *cmd[]) {
  int pipefd[2];

  // Create a pipe: pipefd[0] = read end, pipefd[1] = write end
  if (pipe(pipefd) == -1)
    error_and_exit("pipe");

  pid_t pid1 = fork();
  if (pid1 < 0)
    error_and_exit("fork");

  if (pid1 == 0) {
    // CHILD 1
    // This child will run cmd1 and send output into the pipe.

    // Replace stdout with the write end of the pipe
    dup2(pipefd[1], STDOUT_FILENO);

    // Close both ends of the pipe in child
    close(pipefd[0]);
    close(pipefd[1]);

    // Execute first command
    execvp(cmd1[0], cmd1);
    error_and_exit("execvp cmd1");
  }

  // Parent continues - fork child 2
  pid_t pid2 = fork();
  if (pid2 < 0)
    error_and_exit("fork");

  if (pid2 == 0) {
    // CHILD 2
    // This child will take input from the pipe and run cmd2
    
    // Replace stdin with the read end of the pipe
    dup2(pipefd[0], STDIN_FILENO);

    // Close both ends of the pipe in child
    close(pipefd[0]);
    close(pipefd[1]);

    // Execute second command
    execvp(cmd2[0], cmd2);
    error_and_exit("execvp cmd2");
  }

  // PARENT

  // Parent must close both ends of the pipe,
  // otherwise children never detect EOF.
  close(pipefd[0]);
  close(pipefd[1]);

  // Wait for both children
  waitpid(pid1, NULL, 0);
  waitpid(pid2, NULL, 0);

  return 0;
}
