/*---------------------------------------------------------------------------------------
--      SOURCE FILE:            processes.c
--
--      PROGRAM:                processes.exe
--
--      DATE:                   January 10, 2018
--
--      DESIGNERS:              Brandon Gillespie
--
--      PROGRAMMERS:            Brandon Gillespie
--
--      NOTES:
--	    Program to complete computations/IO using proccesses.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <time.h>
#include <sys/time.h>

int main() {
  //execl("~/Documents/COMP8005/A1/execute");
  int pid;

  pid = fork();

  if (pid == 0) {
    //execl("/bin/ls", "ls" "-l", (char*)0);
    execl("/home/brandondg/Documents/COMP8005/A1/execute", "execute", (char*)0);
    perror("Exec fail ");
    exit(1);
  }

  /*
  clock_t begin = clock();
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  clock_t end = clock();

  double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

  printf("Time of day: %f \n", time_spent);
  */

  return 0;
}
