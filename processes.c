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
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <gmp.h>
#include "primedecompose.h"

// Constants
#define MSGSIZE 64
#define MAX_FACTORS	1024

// Function prototypes
void execute(int p[2]);
void parent(int p[2], FILE *f);

// Globals
mpz_t dest[MAX_FACTORS]; // must be large enough to hold all the factors!

int main() {
  int pid, pfd[2];
  pid_t wpid;
  int status = 0;
  FILE *f;

  /*----- Open the pipe -----------*/
  if (pipe(pfd) < 0) {
    perror("pipe call");
    exit(1);
  }
  if ((f = fopen("processresults", "a")) == 0) {
		fprintf(stderr, "fopen\n");
		exit(1);
	}

  for (size_t i = 0; i < 5; i++) {
    if ((pid = fork()) <= 0) {
      break;
    }
  }

  if (pid == 0) {
    execute(pfd);
  }

  while ((wpid = wait(&status)) > 0);

  if (pid > 0) {
    parent(pfd, f);
    printf("Parent finished\n");
  }
  fclose(f);
  return 0;
}

/*---------------------------------------------------------------------------------------
--      SOURCE FILE:            processes.c
--
--      FUNCTION HEADER:        void execute(int p[2])
--
--      DATE:                   January 13, 2018
--
--      DESIGNERS:              Brandon Gillespie
--
--      PROGRAMMERS:            Brandon Gillespie
--
---------------------------------------------------------------------------------------*/
void execute(int p[2]) {
  struct timeval begin, end;
  char tm[MSGSIZE];
  char *num = "43980248392224";

  close(p[0]);

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

  sprintf(tm, "%lu.%06lu %lu.%06lu %lu.%06d", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), i);
  write(p[1], tm, MSGSIZE);

  exit(0);
}

/*---------------------------------------------------------------------------------------
--      SOURCE FILE:            processes.c
--
--      FUNCTION HEADER:        void parent(int p[2], FILE *f)
--
--      DATE:                   January 13, 2018
--
--      DESIGNERS:              Brandon Gillespie
--
--      PROGRAMMERS:            Brandon Gillespie
--
---------------------------------------------------------------------------------------*/
void parent(int p[2], FILE *f) {
  int nread, c, dif, avg;
  char buf[MSGSIZE];

  dif = avg = c = 0;

  close (p[1]);    /* close the write descriptor */

  printf("--------------------------------------------------------------------\n");
  printf("Processes    |    Start Time   |    End Time     | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  for (;;) {
    switch (nread = read(p[0], buf, MSGSIZE)) {
      case -1:
      case 0:
        printf("--------------------------------------------------------------------\n");
        printf("The Average: %d\n", avg / c);
	      exit(0);
        break;
      default:
        sscanf(buf + 38, "%d", &dif);
        avg += dif;
        ++c;
        printf("Process Time: %s\n", buf);
        fprintf(f, "%s\n", buf);
    }
  }
}
