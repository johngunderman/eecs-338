#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

const int STRLEN = 128;

void
main (void) {

  int pid;
  int pid1;
  int pid2;
  char* hostname;
  char* username;
  char* ctimer;
  time_t timer; // will contain the current time in seconds since epoch.
  char* cwd; // current working directory


  pid = getpid();
  hostname = malloc(sizeof(char) * STRLEN);
  username = malloc(sizeof(char) * STRLEN);
  ctimer = malloc(sizeof(char) * STRLEN);
  cwd = malloc(sizeof(char) * STRLEN * 2);

  /* Library/System calls go here: */
  timer = time(NULL);
  ctimer = ctime(&timer);
  cuserid(username);
  gethostname(hostname, STRLEN);
  getcwd(cwd, STRLEN * 2);


  printf("I am teh parentz, all your childs are belong to me.\n");
  printf("PID:\t\t%d\n", pid);
  printf("Hostname:\t%s\n", hostname);
  printf("Username:\t%s\n", username);
  printf("Current Time:\t%s", ctimer);
  printf("CWD:\t\t%s\n", cwd);

  free(hostname);
  free(username);
  free(cwd);
  /* ctimer points to static memory, so we don't need to free it. */


  /* Here begin the child stuffs, along with numerous HIPPO references */

  putenv("HIPPO=11");
  

  /* Child Process C1: */
  pid1 = fork();

  if (pid1 == 0) { 		/* We are in the child process */
    
    printf("Hi! I'm a child! (C1)\n");
    printf("My name is %d, and my mommy's name is %d!\n", getpid(), getppid());
    fflush(NULL);

    exit(0);
  } else { 			/* we are in the parent process */
  }

  /* Child process C2: */
  pid2 = fork();

  if (pid2 == 0) { 		/* We are in the child process */

    printf("Hi! I'm a child! (C2)\n");
    printf("My name is %d, and my mommy's name is %d!\n", getpid(), getppid());    
    fflush(NULL);

    exit(0);
  } else { 			/* we are in the parent process */
  }

  

  exit(0);
}
