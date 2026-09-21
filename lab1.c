#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *lineptr = NULL;
  size_t size = 0;
  printf("Hello, please enter some text: ");
  ssize_t num_char = getline(&lineptr, &size, stdin);
  if (num_char == -1) {
    perror("someting went wrong");
    free(lineptr);
    exit(EXIT_FAILURE);
  }
  printf("You entered : %s", lineptr);

  // tokenizing
  char *saveptr = NULL;
  char *token = strtok_r(lineptr, " ", &saveptr);
  printf("Token: ");
  while (token != NULL) {

    printf("%s\n", token);
    token = strtok_r(NULL, " ", &saveptr);
  }
  free(lineptr);
}
