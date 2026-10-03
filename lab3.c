#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 5

int main(void) {
  char *history[SIZE] = {NULL};
  int n = 0;

  while (1) {
    printf("enter input: ");

    char *line = NULL;
    size_t cap = 0;
    ssize_t len = getline(&line, &cap, stdin);
    if (len == -1) {
      free(line);
      break;
    }
    if (len > 0 && line[len - 1] == '\n')
      line[len - 1] = '\0';

    free(history[n % SIZE]);
    history[n % SIZE] = line;
    n++;

    if (strcmp(line, "print") == 0) {
      int start = (n > SIZE) ? n - SIZE : 0;
      for (int i = start; i < n; i++)
        printf("%s\n", history[i % SIZE]);
    }
  }

  for (int i = 0; i < SIZE; i++)
    free(history[i]);
  return 0;
}
