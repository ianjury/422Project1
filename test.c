/*
Ian Jury
TCSS 422. Spring 2017
Project 1 -- MASH
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<sys/wait.h>
#define SIZE 255

int main(int argc, char const *argv[]) {
  int p1;
  int p2;
  int p3;

  p1 = fork();

  if (p1 == 0) { //child process
    printf("Child process 1. PID = %d\n", getpid());
  } if (p1 > 0) { //parent process
    wait(NULL);
    printf("Parent process 1. PID = %d. Child process = %d\n", getpid(), p1);
    p2 = fork();
    if (p2 == 0) { //child process 2
      printf("Child process 2. PID = %d\n", getpid());
    } if (p2 > 0) { //parent process 2
      wait(NULL);
      printf("Parent process 2. PID = %d. Child process = %d\n", getpid(), p2);
    }

  }


  return 0;
}
