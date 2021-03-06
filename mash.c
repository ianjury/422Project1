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
#define SIZE 255

void mash(char c1[], char c2[], char c3[], char file[]);

int main(int argc, char const *argv[]) {
  char command1[SIZE];    //first command
  char command2[SIZE];    //second
  char command3[SIZE];    //third
  char fileName[SIZE];    //name of file to process
  int i;
  char c;

  //for testing later, to see if any input was given to a command.
  command1[0] = 0;
  command2[0] = 0;
  command3[0] = 0;

  //get first command
  printf("mash-1>");
  i = 0;
  while ((c=fgetc(stdin)) != '\n') {
    command1[i++] = c;
  }
  command1[i] = '\0';
  //fgets(command1, sizeof buffer, stdin);


  //get second command
  printf("mash-2>");
  i = 0;
  while ((c=fgetc(stdin)) != '\n') {
    command2[i++] = c;
  }
  command2[i] = '\0';

  //get third command
  printf("mash-3>");
  i = 0;
  while ((c=fgetc(stdin)) != '\n') {
    command3[i++] = c;
  }
  command3[i] = '\0';

  //get file name
  printf("file>");
  i = 0;
  while ((c=fgetc(stdin)) != '\n') {
    fileName[i++] = c;
  }
  fileName[i] = '\0';

  mash(command1, command2, command3, fileName);

  return 0;
}

/*
Method that handles all of the heavy lifting. It takes the commands and the
file name and runs all 3 (or however many have been entered) and runs them
on the file. Fork is used to split the processes and then exec is used to run
the new processes (move to a new program) to improve speed.
*/
void mash(char c1[], char c2[], char c3[], char file[]) {
    int p1;
    int p2;
    int p3;

    if ((p1 = fork()) < 0) {
      printf("First fork failed.\n");
    }

    if (p1 == 0) {  //child process 1
        if (c1[0] != 0) { //if a command was given to this one
            char *myargs[8]; //5 is max # of args - as specified
            char *str =strtok(c1, " ");
            int n = 0;
            while(str != NULL) {
                myargs[n] = str;
                str = strtok(NULL, " ");
                n++;
            }
            myargs[n] = strdup(file);
            myargs[n+1] = NULL;

            //test for invalid/execute
            if (execvp(myargs[0], myargs) == -1) {
                printf("[SHELL 1] STATUS CODE = -1\n");
            }
        }
    }
    if (p1 > 0) { //parent process 1
      if ((p2 = fork()) < 0) {
        printf("Second fork failed.\n");
      }

      if (p2 == 0) { //child process 2
          if (c2[0] != 0) { //if a command was given to this one
              char *myargs[8]; //5 is max # of args - as specified
              char *str =strtok(c2, " ");
              int n = 0;
              while(str != NULL) {
                  myargs[n] = strdup(str);
                  str = strtok(NULL, " ");
                  n++;
              }
              myargs[n] = strdup(file);
              myargs[n+1] = NULL;
              //test for invalid/execute
              if (execvp(myargs[0], myargs) == -1) {
                  printf("[SHELL 2] STATUS CODE = -1\n");
              }
          }
      }
       if (p2 > 0) { //parent process 2
        if ((p3 = fork()) < 0) {
          printf("Third fork failed.\n");
        }

        if (p3 == 0) {   // Child process 3
            if (c3[0] != 0) { //if a command was given to this one
                char *myargs[8]; //5 is max # of args - as specified
                char *str =strtok(c3, " ");
                int n = 0;
                while(str) {
                    myargs[n] = strdup(str);
                    str = strtok(NULL, " ");
                    n++;
                }
                myargs[n] = strdup(file);
                myargs[n+1] = NULL;
                //test for invalid/execute
                if (execvp(myargs[0], myargs) == -1) {
                    printf("[SHELL 3] STATUS CODE = -1\n");
                }
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
}
