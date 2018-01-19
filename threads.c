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
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#define MSGSIZE 64

void* execute();

int main() {
  pthread_t ths[5];
  void* bfs[5];
  int avg, dif;
  FILE *f;

  if ((f = fopen("threadresults", "a")) == 0) {
		fprintf(stderr, "fopen\n");
		exit(1);
	}

  for (size_t i = 0; i < 5; i++) {
    pthread_create(&ths[i], NULL, execute, NULL);
  }
  for (size_t i = 0; i < 5; i++) {
    pthread_join(ths[i], &bfs[i]);
  }

  printf("--------------------------------------------------------------------\n");
  printf("Threads     |    Start Time   |    End Time     | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  for (size_t i = 0; i < 5; i++) {
    sscanf((char *)bfs[i] + 38, "%d", &dif);
    avg += dif;
    printf("Thread Time: %s\n", (char *)bfs[i]);
    fprintf(f, "%s\n", (char *)bfs[i]);
  }
  printf("--------------------------------------------------------------------\n");
  printf("The Average: %d\n", avg / 5);

  return 0;
}

void* execute() {
  struct timeval begin, end;
  char *buf = (char *)malloc(MSGSIZE);

  gettimeofday(&begin, NULL);

  
  for (size_t i = 0; i < 10; i++) {
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
    printf("TAKE UP TIME : %d \n", (int)getpid());
  }
  /*
  for (size_t i = 0; i < 50000000; i++) {
    float p = 1513252432.234235242534;
    p *= 10000.432424243424432432;
    p /= 10000.32423242423;
  } */

  gettimeofday(&end, NULL);

  sprintf(buf, "%lu.%06lu %lu.%06lu %lu.%06lu", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
  return (void *) buf;
}
