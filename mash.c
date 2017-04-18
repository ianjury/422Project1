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

void mash(char c1[], char c2[], char c3[], char file[]);

int main(int argc, char const *argv[]) {
  char command1[SIZE];    //first command
  char command2[SIZE];    //second
  char command3[SIZE];    //third
  char fileName[SIZE];    //name of file to process
  char buffer[SIZE];

  //for testing later, to see if any input was given to a command.
  command1[0] = 0;
  command2[0] = 0;
  command3[0] = 0;

  //get first command
  printf("mash-1>");
  if (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%s", command1);
  }

  //get second command
  printf("mash-2>");
  if (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%s", command2);
  }

  //get third command
  printf("mash-3>");
  if (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%s", command3);
  }

  //get file name
  printf("file>");
  if (fgets(buffer, sizeof buffer, stdin) != NULL) {
    sscanf(buffer, "%s", fileName);
  }

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
  int status;
  int p1;
  int p2;
  int p3;
  p1 = fork();

  if (p1 == 0) { //child process 1. Do work
    if (c1[0] != 0) { //if a command was given to this one
      strcat(c1, " ");
      strcat(c1, file);
      system(c1);
    } else {
      printf("No command given for 1\n");
    }
  }
  if (p1 > 0) { //parent process 1. Make more children
    p2 = fork();
    if ( p2 == 0) { //child process 2. Do work.
      if (c2[0] != 0) { //if a command was given to this one
        strcat(c2, " ");
        strcat(c2, file);
        system(c2);
      }
    }
    if (p1 > 0) { //parent process 2. Make another child.
      p3 = fork();
      if (p3 == 0) {    //cild process 3. Do work
        if (c3[0] != 0) { //if a command was given to this one
          strcat(c3, " ");
          strcat(c3, file);
          system(c3);
        }
      }
      if (p3 > 0) { //final parent process. Wait.
        //wait(&status);
      }
    }
    wait(NULL);
    //printf("Done waiting on children %d %d %d", p1, p2, getpid());
    exit(1);
  }




}
