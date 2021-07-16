#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include "disastrOS.h"
#include "disastrOS_syscalls.h"
#include "strutture.h"

void leggi(){
	
	printf(RED);
    printf("LEGGI\n");
    printf(RESET);
    
	coda* coda = running->syscall_args[0];
	char* s = running->syscall_args[1];
	int size = running->syscall_args[2];
	
    int i=0;
    //se lo spazio disponibile per leggere è 0 allora restituisco 0 avvisando che ho letto 0 caratteri
    if(coda->reading_space==0){
        running->syscall_retvalue=0;
        print_coda(coda);
        return;
    }
    //finchè c'è spazio per la lettura e finchè non ho raggiunto il massimo numero di caratteri che devo leggere
    while(i<size && coda->reading_space>0){
        //leggo dalla coda e copio il carattere letto nella stringa "s"
        s[i]=coda->buffer[coda->reading_index];
        //rimetto il carattere letto nella coda al valore di default (serve solo per avere una prova visiva di come
        //è la coda)
        coda->buffer[coda->reading_index]='_';
        //aggiorno i parametri
        coda->reading_index=(coda->reading_index+1)%100;
        coda->reading_space--;
        coda->writing_space++;
        i++;
    }
    print_coda(coda);
    running->syscall_retvalue=i;
    
}
