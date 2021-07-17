#include <stdio.h>
#include <unistd.h>
#include <poll.h>
#include "strutture.h"
#include "disastrOS.h"

//struttura che conterrà le code
lista_code lista;

// we need this to handle the sleep state
void sleeperFunction(void* args){
  printf("Hello, I am the sleeper, and I sleep %d\n",disastrOS_getpid());
  while(1) {
    getc(stdin);
    //disastrOS_printStatus();
  }
}

void childFunction(void* args){
  printf("Hello, I am the child function %d\n",disastrOS_getpid());
  printf("I will iterate a bit, before terminating\n");
  
  //aggiunto da me----->
  
	//apro la coda desiderata
	char s[64];
	int ret=0;
	
	//prendo il pid del processo in modo che non tutti i processi eseguano le stesse chiamate di syscall
	//con lo stesso ordine
	int a=disastrOS_getpid();
	
	
	
	//il primo processo scrive in tutto 20 char mentre il secondo processo legge in tutto 20 char
	//la differenza sta nel fatto che il primo processo scrive 4 char alla volta, mentre il secondo processo ne
	//legge 5 alla volta, quindi quello che si succede è:
	
	//P1 SCRIVE 4			coda = AAAA
	///P2 LEGGE 4			coda = ____
	//P1 SCRIVE 4			coda = AAAA
	///P2 LEGGE 1			coda = AAA 			///P1 legge 1 solo char poichè ogni ciclo prevede la lettura di 5 caratteri
												///e avendone letti già 4 ne deve leggere solamente 1 per terminare il ciclo	
	//P1 SCRIVE 4			coda = AAAAAAA
	///P2 LEGGE 5			coda = AA
	//P1 SCRIVE 4			coda = AAAAAA
	///P2 LEGGE 5			coda = A
	//P1 SCRIVE 5			coda = AAAAA
	///P2 LEGGE 5			coda = _____

	coda* coda1=apri_coda("coda1");
	
	if(a==2){
		ret=0;
		for(int i=0;i<5;i++){
			ret=scrivi_coda_syscall(coda1,"AAAA",4);
			printf(RED);
			printf("PID:%d  HA SCRITTO:%d\n",disastrOS_getpid(),ret);
			printf(RESET);
			sleep(10);
		}
	}
	else if(a==3){
		int count=0;
		int index=0;
		ret=0;
		for(int i=0; i<4; i++){
			printf(GREEN);
			printf("i:   %d\n",i);
			printf(RESET);
			while(count<5){
				ret=leggi_coda_syscall(coda1,s+index,5-count);
				printf(RED);
				printf("PID:%d  HA LETTO:%d\n",disastrOS_getpid(),ret);
				printf(RESET);
				count+=ret;
				index+=ret;
				printf("COUNT:%d\n",count);
				sleep(10);
			}
			count=0;
		}
	}
	printf(GREEN);
	printf("S:%s\n",s);
	printf(RESET);
	chiudi_coda("coda1");
	//<------aggiunto da me


  int type=0;
  int mode=0;
  int fd=disastrOS_openResource(disastrOS_getpid(),type,mode);
  printf("fd=%d\n", fd);
  printf("PID: %d, terminating\n", disastrOS_getpid());

/*
  for (int i=0; i<(disastrOS_getpid()+1); ++i){
    printf("PID: %d, iterate %d\n", disastrOS_getpid(), i);
    disastrOS_sleep((20-disastrOS_getpid())*5);
  }
*/
  disastrOS_exit(disastrOS_getpid()+1);


}


void initFunction(void* args) {
  disastrOS_printStatus();
  printf("hello, I am init and I just started\n");
  disastrOS_spawn(sleeperFunction, 0);
  
  printf("I feel like to spawn 10 nice threads\n");
  int alive_children=0;
  //for (int i=0; i<10; ++i) {
  for (int i=0; i<2; ++i) {						//<---cambiato ora ne spawna solo 2 di processi
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
  print_lista_code();
  printf("shutdown!");
  disastrOS_shutdown();
}

int main(int argc, char** argv){
	
	//inizializzo la struttura che conterrà le code
	lista=init_lista_code();										//<---aggiunto da me
	printf(RED);													//<---aggiunto da me
	print_lista_code();												//<---aggiunto da me
	printf(RESET);													//<---aggiunto da me
	
	
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
