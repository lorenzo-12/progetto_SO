#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include "strutture.h"

#define RED     "\x1b[31m"
#define RESET   "\x1b[0m"
#include "disastrOS.h"
lista_code lista;

// we need this to handle the sleep state
void sleeperFunction(void* args){
  printf("Hello, I am the sleeper, and I sleep %d\n",disastrOS_getpid());
  while(1) {
    getc(stdin);
    disastrOS_printStatus();
  }
}

void childFunction(void* args){
  printf("Hello, I am the child function %d\n",disastrOS_getpid());
  printf("I will iterate a bit, before terminating\n");
  
	coda* coda1=apri_coda("coda1");
	char s[64];
	int ret=0;
	int a=disastrOS_getpid();
	
	if(a%2==0){
		while(!ret){
			ret=leggi_coda_syscall(coda1,s,5);
			printf("HO LETTO:%d\n",ret);
			sleep(10);
		}
		ret=0;
		while(!ret){
			ret=scrivi_coda_syscall(coda1,"BBBBB",5);
			printf("HO SCRITTO:%d\n",ret);
			sleep(10);
		}
	}
	else{
		while(!ret){
			ret=scrivi_coda_syscall(coda1,"BBBBB",5);
			printf("HO SCRITTO:%d\n",ret);
			sleep(10);
		}
		ret=0;
		while(!ret){
		ret=leggi_coda_syscall(coda1,s,5);
		printf("HO LETTO:%d\n",ret);
		sleep(10);
		}
	}
	
	print_coda(coda1);

  
  int type=0;
  int mode=0;
  int fd=disastrOS_openResource(disastrOS_getpid(),type,mode);
  printf("fd=%d\n", fd);
  printf("PID: %d, terminating\n", disastrOS_getpid());

  for (int i=0; i<(disastrOS_getpid()+1); ++i){
    printf("PID: %d, iterate %d\n", disastrOS_getpid(), i);
    disastrOS_sleep((20-disastrOS_getpid())*5);
  }
  disastrOS_exit(disastrOS_getpid()+1);
}


void initFunction(void* args) {
  disastrOS_printStatus();
  printf("hello, I am init and I just started\n");
  disastrOS_spawn(sleeperFunction, 0);
  
  coda* codaf=apri_coda("coda1");
  char b[100];
  for(int i=0; i<100; i++){
	  b[i]='A';
  }
  int ret=scrivi_coda_syscall(codaf,b,100);
  printf(MAGENTA);
  printf("HO SCRITTO: %d\n",ret);
  printf(RESET);
  print_coda(codaf);
  
  printf("I feel like to spawn 10 nice threads\n");
  int alive_children=0;
  for (int i=0; i<10; ++i) {
    int type=0;
    int mode=DSOS_CREATE;
    printf("mode: %d\n", mode);
    printf("opening resource (and creating if necessary)\n");
    int fd=disastrOS_openResource(i,type,mode);
    printf("fd=%d\n", fd);
    disastrOS_spawn(childFunction, 0);
    alive_children++;
  }

  disastrOS_printStatus();
  int retval;
  int pid;
  while(alive_children>0 && (pid=disastrOS_wait(0, &retval))>=0){ 
    disastrOS_printStatus();
    printf("initFunction, child: %d terminated, retval:%d, alive: %d \n",
	   pid, retval, alive_children);
    --alive_children;
  }
  printf("shutdown!");
  disastrOS_shutdown();
}

int main(int argc, char** argv){
  lista=init_lista_code();
  printf(RED);
  print_lista_code();
  printf(RESET);
  char* logfilename=0;
  if (argc>1) {
    logfilename=argv[1];
  }
  // we create the init process processes
  // the first is in the running variable
  // the others are in the ready queue
  printf("the function pointer is: %p", childFunction);
  // spawn an init process
  printf("start\n");
  disastrOS_start(initFunction, 0, logfilename);
  return 0;
}
