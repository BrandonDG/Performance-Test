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
#include <sys/wait.h>

#define MSGSIZE 64

void execute(int p[2]);
void parent(int p[2]);

/*------- Message Strings -------------*/
char *msg1 = "Hello World";
char *msg2 = "Goodbye World";

int main() {
  //execl("~/Documents/COMP8005/A1/execute");
  int pid, pfd[2];
  pid_t wpid;
  int status = 0;

  /*----- Open the pipe -----------*/
  if (pipe(pfd) < 0) {
    perror("pipe call");
    exit(1);
  }

  /*
  pid = fork();


  if (pid == 0) {
    //execl("/bin/ls", "ls" "-l", (char*)0);
    execl("/home/brandondg/Documents/COMP8005/A1/execute", "execute", (char*)0);
    perror("Exec fail ");
    exit(1);
  } */

  for (size_t i = 0; i < 8; i++) {
    if ((pid = fork()) <= 0) {
      break;
    }
  }

  if (pid == 0) {
    /*
    execl("/home/brandondg/Documents/COMP8005/A1/execute", "execute", (char*)0);
    perror("Exec fail ");
    exit(1); */
    execute(pfd);
  }

  while ((wpid = wait(&status)) > 0);

  if (pid > 0) {
    parent(pfd);
    printf("Parent finished\n");
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

void execute(int p[2]) {
  struct timeval begin, end;
  char tm[MSGSIZE];

  close(p[0]);

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
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");
  printf("TAKE UP TIME\n");

  gettimeofday(&end, NULL);
  /*
  printf("End Time = %lu.%06lu\n", end.tv_sec, end.tv_usec);

  printf("Total Time: %lu.%06lu\n", (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));

  printf("--------------------------------------------------------------------\n");
  printf("Threads   |     Start Time     |     End Time      | Total Execution\n");
  printf("--------------------------------------------------------------------\n");
  printf("Threads   | %lu.%06lu  | %lu.%06lu | %lu.%06lu\n", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
  */

  /*
  for (count = 0; count < 3; count ++) {
    write (p[1], msg1, MSGSIZE);
    sleep (3);
  } */
  sprintf(tm, "%lu.%06lu %lu.%06lu %lu.%06lu", begin.tv_sec, begin.tv_usec, end.tv_sec, end.tv_usec,
        (end.tv_sec - begin.tv_sec), (end.tv_usec - begin.tv_usec));
  write(p[1], tm, MSGSIZE);
  //write(p[1], msg2, MSGSIZE);
  exit(0);
}

void parent(int p[2]) {
  int nread, c, dif, avg;
  //double avg;
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
        printf("The Average: %d\n", avg / c);
	      exit(0);
        break;
      default:
        sscanf(buf + 38, "%d", &dif);
        // (18*2)+2 = 38
        avg += dif;
        ++c;
        printf("Process Time: %s\n", buf);
      /*
        if (strcmp (buf, msg2) == 0) {
	        printf("End of Conversation\n");
	        exit(0);
        }
        else {
          sscanf(buf, "%f %f %f", dif, dif, dif);
          avg += dif;
          ++c;
	        printf("Process Time: %s\n", buf);
        }
        */
      /*
      case -1:
      case 0:
	    printf ("(pipe empty)\n");
	    sleep(1);
        break;
      default:
        if (strcmp (buf, msg2) == 0)
        {
	      printf ("End of Conversation\n");
	      exit(0);
        }
        else
	      printf ("MSG = %s\n", buf);
        */

    }
  }
}
