/* COMP 530: Tar Heel SHell
3 *
 * This file implements functions related to launching
 * jobs and job control.
 */

#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "thsh.h"

static char ** path_table;
//e -> string
//path_table -> e;
/* Initialize the table of PATH prefixes.
 *
 * Split the result on the parenteses, and
 * remove any trailing '/' characters.
 * The last entry should be a NULL character.
 *
 * For instance, if one's PATH environment variable is:
 *  /bin:/sbin///
 *
 * Then path_table should be:
 *  path_table[0] = "/bin"
 *  path_table[1] = "/sbin"
 *  path_table[2] = '\0'
 *
 * Hint: take a look at getenv().  If you use getenv, do NOT
 *       modify the resulting string directly, but use
 *       malloc() or another function to allocate space and copy.
 *
 * Returns 0 on success, -errno on failure.
 */
int init_path(void) {
  /* Lab 0: Your code here */
   char *temp = getenv("PATH"); // use temp to copy the string that we will allocate memory for
   char *p = malloc(strlen(temp)+1); // guarantees memory for PATH
   strcpy(p, temp); // persistent memory that we can  write to
   int cNum = 1;
   if(strlen(p) == 0){
	cNum = 0;
   }

   for (int i = 0; p[i]; i++) {
	if(p[0] == ':') {
		p[0] = '\0';
		cNum = 0;
		break;
	}
	if(p[i] == ':'){
         	cNum++;
        }
   }

   path_table = malloc(sizeof(char *)*(cNum+1));
   int ptCount = 0;
   if(cNum > 0){
	path_table[ptCount] = &p[0]; //storing beginning of first string

	for (int i = 0; p[i]; i++){
		if(p[i] == '/' && (p[i+1] == '\0' || p[i+1] == '/')){
            		p[i] = '\0';
        	}

		if(p[i] == ':') {
	    		p[i] = '\0';
	    		ptCount++;
	    		path_table[ptCount] = &p[i+1]; //storing pointer to address of next string in PATH
		}
	}
   }
   return 0;
}

/* Debug helper function that just prints
 * the path table out.
 */
void print_path_table() {
  if (path_table == NULL) {
    printf("XXXXXXX Path Table Not Initialized XXXXX\n");
    return;
  }

  printf("===== Begin Path Table =====\n");
  for (int i = 0; path_table[i]; i++) {
    printf("Prefix %2d: [%s]\n", i, path_table[i]);
  }
  printf("===== End Path Table =====\n");
}
