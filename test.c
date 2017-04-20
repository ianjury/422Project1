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

  if (p1 == 0) {              //child process 1
  char *myargs[3];
    myargs[0] = strdup("wc"); // program: "wc" (word count)
    myargs[1] = strdup("test.txt"); // argument: file to count
    myargs[2] = NULL; // marks end of array
    execvp(myargs[0], myargs); // runs word count
    //printf("Child process 1. PID = %d\n", getpid());

  } if (p1 > 0) { //parent process
    p2 = fork();

    if (p2 == 0) { //child process 2
      char *myargs[3];
      myargs[0] = strdup("ls");
      myargs[1] = strdup("test.txt"); // argument: file to count
      myargs[2] = NULL; // marks end of array
      execvp(myargs[0], myargs);

    } if (p2 > 0) { //parent process 2
      p3 = fork();
      wait(NULL);
      if (p3 == 0) {   // Child process 3
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("test.txt"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        //printf("!!!!Child process 2. PID = %d\n", getpid());
        execvp(myargs[0], myargs);
      }
      if (p3 > 0) { //parent process 3
        wait(NULL);
      }
      //wait(NULL);
      //printf("Parent process 2. PID = %d. Child process = %d\n", getpid(), p2);
    }
    wait(NULL); //first parent waits for all children
    printf("Finished waiting for child processes %d %d %d\n", p1, p2, p3);
  }


  return 0;
}
