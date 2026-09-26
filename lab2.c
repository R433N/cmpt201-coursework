#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
int main(void) {

  char *lineptr = NULL;

  size_t size = 0;
  while (1) {

    printf("Enter programs to run.\n>");
    ssize_t numchar = getline(&lineptr, &size, stdin);
    if (numchar == -1) {
      perror("error");
      free(lineptr);
      exit(EXIT_FAILURE);
    }
    // tokenizing now
    char *saveptr = NULL;
    char *token = strtok_r(lineptr, " \t\n", &saveptr);
    printf("Token: ");
    if (token == NULL) {
      continue;
    }
    pid_t pid = fork();
    if (pid < 0) {
      perror("fork");
      continue;
    } else if (pid == 0) {
      execlp(token, token, NULL);
      printf("Exec failure\n");
      _exit(EXIT_FAILURE);
    } else {
      int status;
      if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
      }
    }
  }

  free(lineptr);
  return 0;
}
