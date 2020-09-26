/* COMP 530: Tar Heel SHell
 *
 * This file implements a table of builtin commands.
 */
#include "thsh.h"
#include <stdlib.h>

struct builtin {
  const char * cmd;
  int (*func)(char *args[MAX_ARGS], int stdin, int stdout);
};


/* Handle a cd command.  */
int handle_cd(char *args[MAX_INPUT], int stdin, int stdout) {

  // You will implement this in Lab 1.
  // Just return 42 for now (for testing).
  return 42;
}

/* Handle an exit command. */
int handle_exit(char *args[MAX_ARGS], int stdin, int stdout) {
  exit(0);
  return 0; // Does not actually return
}



static struct builtin builtins[] = {{"cd", handle_cd},
				    {"exit", handle_exit},
				    {NULL, NULL}};

/* This function checks if the command (args[0]) is a built-in.
 * If so, call the appropriate handler, and return 1.
 * If not, return 0.
 *
 * stdin and stdout are the file handles for standard in and standard out,
 * respectively. These may or may not be used by individual builtin commands.
 *
 * Places the return value of the command in *retval.
 *
 * stdin and stdout should not be closed by this command.
 *
 * In the case of "exit", this function will not return.
 */
int handle_builtin(char *args[MAX_ARGS], int stdin, int stdout, int *retval) {
//  int rv = 0;
  // Lab 0: Your Code Here
  // Comment this line once implemented.  This just suppresses
  // the unused variable warning from the compiler.
  //  char **input = malloc(strlen(*args)); // allocate memory for command input
  //  strcpy(*input, *args); // copy args into our variable

  // Initialize - another pointer

  // Cases: cd, exit, non built- in

  for (int i = 0; args[i]; i++) {

      if (strcmp(args[i], builtins[0].cmd) == 0) { // cd check
         *retval = handle_cd(args, stdin, stdout);
	 return *retval;
      } else if (strcmp(args[i], builtins[1].cmd) == 0) { // exit check
         *retval = handle_exit(args, stdin, stdout);
	 return *retval;
      } else { // If command is not a built-in
         *retval = 0;
      }
  }

  (void) builtins;
  return *retval;
}
