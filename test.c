/*
Ian Jury
TCSS 422. Spring 2017
Project 1 -- MASH
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char const *argv[]) {
  int p1;
  int p2;
  int p3;
  char *myArgs[3];

  if ((p1 = fork()) < 0) {
    printf("First fork failed.\n");
  }

  if (p1 == 0) {  //child process 1
  char *myargs[4];
    myargs[0] = strdup("wc");
    myargs[1] = strdup("test.txt");
    //myargs[2] = strdup("");
    myargs[2] = NULL;
    if (execvp(myargs[0], myargs) == -1) {//test for invalid/execute
      printf("[SHELL 1] STATUS CODE = -1\n");
    }
  } if (p1 > 0) { //parent process 1
    if ((p2 = fork()) < 0) {
      printf("Second fork failed.\n");
    }

    if (p2 == 0) { //child process 2
      char *myargs[3];
      myargs[0] = strdup("ls");
      myargs[1] = strdup("test.txt"); // argument: file to count
      myargs[2] = NULL; // marks end of array
      if (execvp(myargs[0], myargs) == -1) {//test for invalid/execute
        printf("[SHELL 2] STATUS CODE = -1\n");
      }
    }
     if (p2 > 0) { //parent process 2
      if ((p3 = fork()) < 0) {
        printf("Third fork failed.\n");
      }

      if (p3 == 0) {   // Child process 3
        char *myargs[3];
        myargs[0] = strdup("wc");
        myargs[1] = strdup("test.txt"); // argument: file to count
        myargs[2] = NULL; // marks end of array
        if (execvp(myargs[0], myargs) == -1) {//test for invalid/execute
          printf("[SHELL 3] STATUS CODE = -1\n");
        }
      }
      if (p3 > 0) { //parent process 3
        //3rd waits for child to finish
        wait(NULL);
      }
      //2nd waits for child to finish
      wait(NULL);
    }
    //1st parent waits for child to finish
    wait(NULL);
  }
  //prevents early execution if exec fails in 1+ case(s)
  if (p1 != 0 && p2 != 0 && p3 != 0) {
      printf("Done waiting on children: %d %d %d\n", p1, p2, p3);
  }

  return 0;
}
