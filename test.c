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
  char *myArgs[3];

  p1 = fork();

  if (p1 == 0) {  //child process 1
  char *myargs[3];
    myargs[0] = strdup("w c");
    myargs[1] = strdup("test.txt");
    myargs[2] = NULL;
    if (execvp(myargs[0], myargs) == -1) {
      printf("[SHELL 1] STATUS CODE = -1\n");
    }
  } if (p1 > 0) { //parent process 1
    p2 = fork();

    if (p2 == 0) { //child process 2
      char *myargs[3];
      myargs[0] = strdup("ls");
      myargs[1] = strdup("test.txt"); // argument: file to count
      myargs[2] = NULL; // marks end of array
      if (execvp(myargs[0], myargs) == -1) {
        printf("[SHELL 2] STATUS CODE = -1\n");
      }
    } if (p2 > 0) { //parent process 2
      p3 = fork();

      if (p3 == 0) {   // Child process 3
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("test.txt"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        if (execvp(myargs[0], myargs) == -1) {    //test for invalid/execute
          printf("[SHELL 3] STATUS CODE = -1\n");
        }
      }
      if (p3 > 0) { //parent process 3
        //wait for child to finish
        wait(NULL);
      }
      wait(NULL);
    }
    //first parent waits for children
    wait(NULL);
  }
  //prevents early execution if exec fails in 1+ case(s)
  if (p1 != 0 && p2 != 0 && p3 != 0) {
      printf("Done waiting on children: %d %d %d\n", p1, p2, p3);
  }

  return 0;
}
