#ifndef BUILTINS_H
#define BUILTINS_H

#include <stddef.h>

struct builtin {
  const char *name;
  int (*handler)(char **);

// Function declarations
int cmd_cd(char **args);
int cmd_echo(char **args);
int cmd_pwd(char **args);
int cmd_env(char **args);
int cmd_help(char **args);
int cmd_exit(char **args);

// Expose builtin command table
extern char *builtin_str[];
extern int (*builtin_func[])(char **);
int lsh_num_builtins();

#endif
