#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <errno.h>

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

  /* Check for malloc errors */
  if (!pid || !hostname || !username || !ctimer || !cwd) {
    errno = 1;
    perror("ERROR upon attempting to malloc");
    errno = 0;
  }

  /* Library/System calls go here: */
  timer = time(NULL);
  timer != -1 ? NULL : perror("ERROR on call to time()"); 

  ctimer = ctime(&timer);
  (int) ctimer != -1 ? NULL : perror("ERROR on call to ctime()"); 

  /* TODO: Apparently we are not supposed to use cuserid. Need to find alternative. */
  cuserid(username);
  (int) cuserid != -1 ? NULL : perror("ERROR on call to cuserid()"); 

  gethostname(hostname, STRLEN);
  errno == 0 ? NULL : perror("ERROR on call to gethostname()"); 

  getcwd(cwd, STRLEN * 2);
  errno == 0 ? NULL : perror("ERROR on call to getcwd()"); 
  


  printf("I am teh parentz, all your childs are belong to me.\n");
  printf("PID:\t\t%d\n", pid);
  printf("Hostname:\t%s\n", hostname);
  printf("Username:\t%s\n", username);
  printf("Current Time:\t%s", ctimer);
  printf("CWD:\t\t%s\n", cwd);



  /* Here begin the child stuffs, along with numerous HIPPO references */

  putenv("HIPPO=11");

  /* Child Process C1: */
  pid1 = fork();
  errno == 0 ? NULL : perror("ERROR on call to fork()"); 

  if (pid1 == 0) { 		/* We are in the child process */
    
    printf("Hi! I'm a child! (C1)\n");
    printf("My name is %d, and my mommy's name is %d!\n", getpid(), getppid());
    fflush(NULL);
    usleep(2000);		/* Sleep for 2 microsec */
    putenv("HIPPO=9");
    printf("9 little Hippopotamus (HIPPO=9) C1\n");
    fflush(NULL);
    usleep(2000);
    putenv("HIPPO=9");
    printf("6 little Hippopotamus (HIPPO=6) C1\n");
    fflush(NULL);
    usleep(2000);
    putenv("HIPPO=3");
    printf("3 little Hippopotamus (HIPPO=3) C1\n");
    
    usleep(2000);
    
    chdir("/");
    execlp("/bin/ls", "ls", "-l", "-h", (char *) NULL);
    errno == 0 ? NULL : perror("ERROR on call to execlp()"); 

    exit(0);
  } else { 			/* we are in the parent process */
  }

  /* Child process C2: */
  pid2 = fork();
  errno == 0 ? NULL : perror("ERROR on call to fork()"); 

  if (pid2 == 0) { 		/* We are in the child process */

    printf("Hi! I'm a child! (C2)\n");
    printf("My name is %d, and my mommy's name is %d!\n", getpid(), getppid());    
    fflush(NULL);
    usleep(2000);
    putenv("HIPPO=8");
    printf("8 little Hippopotamus (HIPPO=8) C2\n");
    fflush(NULL);
    usleep(2000);
    putenv("HIPPO=5");
    printf("5 little Hippopotamus (HIPPO=5) C2\n");
    usleep(2000);
    putenv("HIPPO=2");
    printf("2 little Hippopotamus (HIPPO=2) C2\n");

    usleep(3000);

    getcwd(cwd, STRLEN * 2);
    printf(" \nC2 is currently operating in %s\n", cwd);

    /* sorta hack to increment the number (increments the ascii value,
     but it works out the same.*/
    printf("The contents of HIPPO + 1 in C2 is %c\n\n", (getenv("HIPPO")[0] + 1));

    exit(0);
  } else { 			/* we are in the parent process */
    putenv("HIPPO=10");
    usleep(1000); 		/* Sleep for 2 microsecs */
    printf("10 little Hippopotamus (HIPPO=10) P\n");
    usleep(2000);
    putenv("HIPPO=7");
    printf("7 little Hippopotamus (HIPPO=7) P\n");
    usleep(2000);
    putenv("HIPPO=4");
    printf("4 little Hippopotamus (HIPPO=4) P\n");
    usleep(2000);
    putenv("HIPPO=1");
    printf("1 little Hippopotamus (HIPPO=1) P\n");
  }


  wait(-1);

  /* Free all of our junk. */
  free(hostname);
  free(username);
  free(cwd);
  /* ctimer points to static memory, so we don't need to free it. */

  exit(0);
}
