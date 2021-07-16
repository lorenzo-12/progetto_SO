#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

typedef struct coda coda;
typedef struct lista_code lista_code;

typedef struct coda{
    char* name;
    int num_ref;
    int writing_space;
    int reading_space;
    int reading_index;
    int writing_index;
    char buffer[100];
    coda* next;
    coda* prev;
}coda;

typedef struct lista_code{
    int num_code;
    coda* first;
    coda* last;
}lista_code;

lista_code lista;

lista_code init_lista_code(){
    lista_code lc;
    lc.num_code=0;
    lc.first=NULL;
    return lc;
}

coda* apri_coda(char* s){
    coda* ret;
    int ok=0;
    coda* aux= lista.first;
    while(aux){
        if(aux->name==s){
            aux->num_ref++;
            return aux;
        }
        aux=aux->next;
    }

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

void chiudi_coda(char* s){
    coda* aux=lista.first;
    coda* tmp;
    if(aux->name==s){
        aux->num_ref--;
        if(aux->num_ref==0){
            lista.first=aux->next;
            lista.num_code--;
        }
    }
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

void print_coda(coda* aux){
    printf(BLUE);
    printf("name: %s\nnum_ref:%d\nwriting_space:%d\nwriting_index:%d\nreading_space:%d\nreading_index:%d\n",
                                    aux->name,aux->num_ref,aux->writing_space,aux->writing_index,aux->reading_space,aux->reading_index);
    printf("%s\n",aux->buffer);
    printf(RESET);
}

int scrivi(coda* coda,char* s,int size){
    int i=0;
    if(coda->writing_space==0) {
        //printf("writing_space=0\n");
        return size;
    }
    while(i<size && coda->writing_space>0){
        coda->buffer[coda->writing_index]=s[i];
        i++;
        coda->writing_index=(coda->writing_index+1)%100;
        coda->writing_space--;
        coda->reading_space++;
    }
    return i;
}

int leggi(coda* coda,char* s, int size){
    int i=0;
    if(coda->reading_space==0){
        //printf("reading_space=0\n");
        return 0;
    }
    while(i<size && coda->reading_space>0){
        s[i]=coda->buffer[coda->reading_index];
        coda->buffer[coda->reading_index]='_';
        coda->reading_index=(coda->reading_index+1)%100;
        coda->reading_space--;
        coda->writing_space++;
        i++;
    }
    return i;
}


