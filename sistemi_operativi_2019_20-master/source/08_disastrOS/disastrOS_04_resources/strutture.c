#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "strutture.h"

///strutture per printare colorato
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

//funzione che inizializza la struttura per contenere le code
lista_code init_lista_code(){
    lista_code lc;
    lc.num_code=0;
    lc.first=NULL;
    return lc;
}


//funzione che serve per aprire una coda utilizzando come nome della coda la stringa in input
//se la coda non esiste già allora ne crea una e restituisce un puntatore a essa
//se invece la coda già esiste allora restituisce un puntatore a essa
coda* apri_coda(char* s){
    coda* ret;
    
    //scorro tutta la lista, se trovo una coda che ha lo stesso nome vuol dire che la coda esiste già
    //quindi restituisco la coda e aggiorno il campo num_ref
    coda* aux= lista.first;
    while(aux){
        if(aux->name==s){
            aux->num_ref++;
            return aux;
        }
        aux=aux->next;
    }
    
    //se la coda non esiste, allora ne creo una e la aggiungo in prima posizione, e poi restituisco un puntatore a essa
    coda* c = (coda*)malloc(sizeof(struct coda));
    c->name=s;
    c->num_ref=1;
    c->writing_space=100;
    c->reading_space=0;
    c->writing_index=0;
    c->reading_index=0;
    memset(c->buffer,'_',100);
    c->next=lista.first;
    c->prev=NULL;
    lista.first=c;
    lista.num_code++;
    return c;
}


//funzione che serve per chiudere una coda
//come per l'apertura, si prende in input la stringa che rappresenta il nome della coda
void chiudi_coda(char* s){
    coda* aux=lista.first;
    coda* tmp;
    //caso in cui la coda che si vuole chiudere è nella prima posizione
    if(aux->name==s){
        aux->num_ref--;
        if(aux->num_ref==0){
            lista.first=aux->next;
            lista.num_code--;
        }
    }
    //cerco la coda all'interno della linked list e quando la trovo decremento il valore di num_ref
    //se questo diventa 0 quello che succede è che si elimina la coda dalla linked list
    while(aux){
        tmp=aux->next;
        if(tmp && tmp->name==s){
            tmp->num_ref--;
            if(tmp->num_ref==0){
                aux->next=tmp->next;
                lista.num_code--;
                break;
            }
        }
        aux=aux->next;
    }
}


//serve per printare a schermo le code attualente aperte
void print_lista_code(){
    printf("num_code: %d\n",lista.num_code);
    coda* aux=lista.first;
    printf(RED);
    while(aux){
        printf("%s -> ",aux->name);
        aux=aux->next;
    }
    if(aux==NULL) printf("null\n");
    printf(RESET);
}

//serve per printare a schermo la struttura di una coda
void print_coda(coda* aux){
    printf(BLUE);
    printf("name: %s   num_ref:%d   writing_space:%d   writing_index:%d   reading_space:%d   reading_index:%d\n",
                                    aux->name,aux->num_ref,aux->writing_space,aux->writing_index,aux->reading_space,aux->reading_index);
    printf("%s\n",aux->buffer);
    printf(RESET);
}



///le funzioni "leggi" e "scrivi" contengono unicamente il codice che dovrà essere aggiunto all'interno della rispettiva
///system call. Tali funzioni verranno commentate una volta aggiunte le system call, ma per il momento sono utili a testare 
///il codice, in modo da capire se quando si scrive si scrive nel modo giusto e se si aggiornano i parametri in modo coerente
///(idem per la lettura)


/*
//funzione che tenta di scrivere nella coda "coda", "size" caratteri della stringa "s"
//viene restituito il numero di caratteri che si sono effettivamente scritti
int scrivi(coda* coda,char* s,int size){
    int i=0;
    //se lo spazio disponibile è 0 allora ritorno subito "0" in modo da avvisare che ho scritto "o" caratteri
    if(coda->writing_space==0) {
        return 0;
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
    return i;
}

//funzione che tenta di leggere nella coda "coda", "size" caratteri e li copia nella stringa "s"
//viene restituito il numero di caratteri che si sono effettivamente letti
int leggi(coda* coda,char* s, int size){
    int i=0;
    //se lo spazio disponibile per leggere è 0 allora restituisco 0 avvisando che ho letto 0 caratteri
    if(coda->reading_space==0){
        return 0;
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
    return i;
}

*/





