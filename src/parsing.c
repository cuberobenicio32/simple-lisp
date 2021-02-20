#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

/* If we are on Windows, compile these functions */
#ifdef _WIN32

/* Fake readline function */
char* readline(char* prompt) {
  fputs(prompt, stdout);
  fgets(buffer, 2048, stdin);
  char* cpy = malloc(strlen(buffer)+1);
  strcpy(cpy, buffer);
  cpy[strlen(cpy)-1] = '\0';
  return cpy;
}

/* Fake add_history function */
void add_history(char* unused) {}

/* Otherwise include the editline headers */
#else
#include <editline/readline.h>
#endif

/* Declare a buffer for user input of size 2048 */
static char input[2048];

int main(int argc, char** argv) {

  /* Define time variables */ 
  int day, month, year;

  /* time_t is arithmetic time type */
  time_t now; 

   /* Obtain current time */
   /* time() returns the current time of the system as a time_t value */
    time(&now);

  /* localtime converts a time_t value to calendar time and */
  /* returns a pointer to a tm structure with its members */
  /* filled with the corresponding values*/
    struct tm *local = localtime(&now);

    day = local->tm_mday; /* Get day of month (1 to 31)*/
    month = local->tm_mon + 1 ; /* Get month of the year (0 to 12)*/
    year = local->tm_year + 1900; /* Get year since 1900 */

  /* Print Version and Exit Information */
  #ifdef _WIN32
  printf("SimpleLisp 0.0.1 on Windows (%02d/%02d/%d) \n", day, month, year);
  #elif __APPLE__
  printf("SimpleLisp 0.0.1 on MacOS (%02d/%02d/%d) \n", day, month, year);
  #elif __linux__
  printf("SimpleLisp 0.0.1 on Linux (%02d/%02d/%d) \n", day, month, year);
  #else
  printf("SimpleLisp 0.0.1 on [UNKNOWN] (%02d/%02d/%d) \n", day, month, year);
  #endif
  puts("Press Ctrl-C to exit\n");

  /* In a never ending loop */
  while (1) {

    /* Output our prompt and get input*/
    char* input = readline("slisp> ");

    /* Add input to history */
    add_history(input);

    /* Echo input back to user */
    printf("%s\n", input);

    /* Free retrieved input */
    free(input);

  }
  return 0;
}
