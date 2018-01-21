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
#include <gmp.h>
#include "primedecompose.h"

// Constants
#define MSGSIZE 64
#define MAX_FACTORS	1024

// Function prototypes
void* execute();

// Globals
mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!

int main() {
  pthread_t ths[5];
  void* bfs[5];
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
    printf("Thread Time: %s\n", (char *)bfs[i]);
    fprintf(f, "%s\n", (char *)bfs[i]);
  }
  printf("--------------------------------------------------------------------\n");
  return 0;
}

/*---------------------------------------------------------------------------------------
--      SOURCE FILE:            threads.c
--
--      FUNCTION HEADER:        void* execute()
--
--      DATE:                   January 13, 2018
--
--      DESIGNERS:              Brandon Gillespie
--
--      PROGRAMMERS:            Brandon Gillespie
--
---------------------------------------------------------------------------------------*/
void* execute() {
  struct timeval begin, end;
  char *buf = (char *)malloc(MSGSIZE);
  char *num = "43980248392224";

  gettimeofday(&begin, NULL);

  mpz_t n;
	int i, l;

	mpz_init_set_str(n, num, 10);
	l = decompose(n, dest);

  gettimeofday(&end, NULL);

  i = end.tv_usec - begin.tv_usec;
  if (i < 0) {
    i *= -1;
  }

  sprintf(buf, "%lu.%06lu %lu.%06lu %lu.%06d", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), i);
  return (void *) buf;
  //return NULL;
}
