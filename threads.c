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
#include <stdlib.h>
#include <unistd.h>
//#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define MSGSIZE 64

//void* run();
void* execute();

int main() {
  pthread_t ths[8];
  void* bfs[8];
  int avg, dif;

  for (size_t i = 0; i < 8; i++) {
    pthread_create(&ths[i], NULL, execute, NULL);
  }
  for (size_t i = 0; i < 8; i++) {
    pthread_join(ths[i], &bfs[i]);
  }

  //printf("FINISHED PARENT\n");

  printf("--------------------------------------------------------------------\n");
  printf("Processes    |    Start Time   |    End Time     | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  for (size_t i = 0; i < 8; i++) {
    sscanf((char *)bfs[i] + 38, "%d", &dif);
    avg += dif;
    printf("Process Time: %s\n", (char *)bfs[i]);
  }
  printf("The Average: %d\n", avg / 8);

  return 0;
}

void* execute() {
  struct timeval begin, end;
  //char buf[MSGSIZE];
  char *buf = (char *)malloc(MSGSIZE);

  gettimeofday(&begin, NULL);
  //printf("Start Time = %lu.%06lu\n", begin.tv_sec, begin.tv_usec);

  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");

  gettimeofday(&end, NULL);
  //printf("End Time = %lu.%06lu\n", end.tv_sec, end.tv_usec);

  sprintf(buf, "%lu.%06lu %lu.%06lu %lu.%06lu", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
  printf("%s\n", buf);

  /*
  printf("Total Time: %lu.%06lu\n", (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));

  printf("--------------------------------------------------------------------\n");
  printf("Threads   |     Start Time     |     End Time      | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  printf("Threads   | %lu.%06lu  | %lu.%06lu | %lu.%06lu\n", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
        */
  return (void *) buf;
}
