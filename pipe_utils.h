#ifndef PIPE_UTILS_H
#define PIPE_UTILS_H

// Runs cmd1 | cmd2
int run_pipeline(char *cmd1[], char *cmd2[]);

// Helper functions (used internally)
void error_and_exit(const char *msg);

#endif
