/*---------------------------------------------------------------------------------------
--      SOURCE FILE:            threads.c
--
--      PROGRAM:                threads.exe
--
--      DATE:                   January 10, 2018
--
--      DESIGNERS:              Brandon Gillespie
--
--      PROGRAMMERS:            Brandon Gillespie
--
--      NOTES:
--	    Program to complete computations/IO using threads.
---------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
//#include <time.h>
#include <sys/time.h>
#include <pthread.h>

//void* run();
void* execute();

int main() {
  pthread_t thread1;
  //double total;

  pthread_create(&thread1, NULL, execute, NULL);
  pthread_join(thread1, NULL);

  return 0;
}

void* execute() {
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
  printf("Threads   |     Start Time     |     End Time      | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  printf("Threads   | %lu.%06lu  | %lu.%06lu | %lu.%06lu\n", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
  return NULL;
}
