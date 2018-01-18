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

#define MSGSIZE 64

void execute(int p[2]);
void parent(int p[2], FILE *f);

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

  for (size_t i = 0; i < 8; i++) {
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

void execute(int p[2]) {
  struct timeval begin, end;
  char tm[MSGSIZE];

  close(p[0]);

  gettimeofday(&begin, NULL);

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
  printf("TAKE UP TIME : %d \n", (int)getpid());
  printf("TAKE UP TIME : %d \n", (int)getpid());
  printf("TAKE UP TIME : %d \n", (int)getpid());
  printf("TAKE UP TIME : %d \n", (int)getpid());
  printf("TAKE UP TIME : %d \n", (int)getpid());
  printf("TAKE UP TIME : %d \n", (int)getpid());

  gettimeofday(&end, NULL);

  sprintf(tm, "%lu.%06lu %lu.%06lu %lu.%06lu", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
  write(p[1], tm, MSGSIZE);

  exit(0);
}

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
