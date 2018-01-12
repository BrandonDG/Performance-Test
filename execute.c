/*---------------------------------------------------------------------------------------
--      SOURCE FILE:            execute.c
--
--      PROGRAM:                execute.exe
--
--      DATE:                   January 11, 2018
--
--      DESIGNERS:              Brandon Gillespie
--
--      PROGRAMMERS:            Brandon Gillespie
--
--      NOTES:
--	    Program to run in each thread/process.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
//#include <time.h>
#include <sys/time.h>

int main() {
  struct timeval begin, end;

  gettimeofday(&begin, NULL);
  printf("Start Time = %lu.%06lu\n", begin.tv_sec, begin.tv_usec);

  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");

  gettimeofday(&end, NULL);
  printf("End Time = %lu.%06lu\n", end.tv_sec, end.tv_usec);

  printf("Total Time: %lu.%06lu\n", (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));

  printf("--------------------------------------------------------------------\n");
  printf("Processes |     Start Time     |     End Time      | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  printf("Process   | %lu.%06lu  | %lu.%06lu | %lu.%06lu\n", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));

  return 0;
}
