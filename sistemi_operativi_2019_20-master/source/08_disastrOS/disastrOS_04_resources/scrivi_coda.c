#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "strutture.h"

void scrivi(){
	
    printf(RED);
    printf("SCRIVI\n");
    printf(RESET);
	
	coda* coda = running->syscall_args[0];
	char* s = running->syscall_args[1];
	int size = running->syscall_args[2];
    int i=0;
    //se lo spazio disponibile è 0 allora ritorno subito "0" in modo da avvisare che ho scritto "o" caratteri
    if(coda->writing_space==0) {
        running->syscall_retvalue=0;
        print_coda(coda);
        return;
    }
    //finchè c'è spazio per la scrittura e finchè non ho raggiunto il numero di caratteri massimo che devo scrivere
    while(i<size && coda->writing_space>0){
        //scrivo all'interno della coda
        coda->buffer[coda->writing_index]=s[i];
        //aggiorno i parametri
        i++;
        coda->writing_index=(coda->writing_index+1)%100;
        coda->writing_space--;
        coda->reading_space++;
    }
    print_coda(coda);
    running->syscall_retvalue=i;
    
}
