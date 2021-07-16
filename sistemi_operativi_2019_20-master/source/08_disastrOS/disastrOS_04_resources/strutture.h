#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///strutture per printare colorato
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"



typedef struct coda coda;
typedef struct lista_code lista_code;

///struttura che rappresenta la coda
typedef struct coda{
    char* name;             
    int num_ref;            //rappresenta il numero di processi che hanno aperto la coda, in questo modo la coda
                            //verrà distrutta solamente quando num_ref=0, cioè quando tutti i processi l'avranno chiusa

    int writing_space;      //rappresenta lo spazio disponibile per la scrittura
    int reading_space;      //rappresenta lo spazio disponibile per la lettura
    int reading_index;      //rappresenta l'indice del buffer da cui partire per leggere
    int writing_index;      //rappresenta l'indice del buffer da cui partire per scrivere
    char buffer[100];       //buffer di 100 elementi che corrisponde alla coda
    coda* next;
    coda* prev;
}coda;


///struttura che rappresenta la struttura che contiene tutte le code
typedef struct lista_code{
    int num_code;           //tiene conto di quante code ci sono
    coda* first;            //puntatore al primo elemento
}lista_code;

lista_code lista;


//funzione che inizializza la struttura per contenere le code
lista_code init_lista_code();


//funzione che serve per aprire una coda utilizzando come nome della coda la stringa in input
//se la coda non esiste già allora ne crea una e restituisce un puntatore a essa
//se invece la coda già esiste allora restituisce un puntatore a essa
coda* apri_coda(char* s);


//funzione che serve per chiudere una coda
//come per l'apertura, si prende in input la stringa che rappresenta il nome della coda
void chiudi_coda(char* s);

//serve per printare a schermo le code attualente aperte
void print_lista_code();

//serve per printare a schermo la struttura di una coda
void print_coda(coda* aux);

///le funzioni "leggi" e "scrivi" contengono unicamente il codice che dovrà essere aggiunto all'interno della rispettiva
///system call. Tali funzioni verranno commentate una volta aggiunte le system call, ma per il momento sono utili a testare 
///il codice, in modo da capire se quando si scrive si scrive nel modo giusto e se si aggiornano i parametri in modo coerente
///(idem per la lettura)



//funzione che tenta di scrivere nella coda "coda", "size" caratteri della stringa "s"
//viene restituito il numero di caratteri che si sono effettivamente scritti

///int scrivi(coda* coda,char* s,int size);

//funzione che tenta di leggere nella coda "coda", "size" caratteri e li copia nella stringa "s"
//viene restituito il numero di caratteri che si sono effettivamente letti

///int leggi(coda* coda,char* s, int size);


