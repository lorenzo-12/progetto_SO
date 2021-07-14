#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct coda coda;
typedef struct lista_code lista_code;

typedef struct coda{
    char* name;
    int num_ref;
    int pid;
    int free_space;
    int index;
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

void apri_coda(char* s){
    int ok=0;
    coda* aux= lista.first;
    while(aux){
        if(aux->name==s){
            ok=1;
            aux->num_ref++;
            break;
        }
        aux=aux->next;
    }

    if(ok==1){
        //printf("gia esiste\n");
        return;
    }
    coda* c = (coda*)malloc(sizeof(struct coda));
    c->name=s;
    c->pid=-1;
    c->num_ref=1;
    c->free_space=100;
    c->index=0;
    memset(c->buffer,'_',100);
    c->next=lista.first;
    c->prev=NULL;
    lista.first=c;
    lista.num_code++;
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
    while(aux){
        printf("%s -> ",aux->name);
        aux=aux->next;
    }
    if(aux==NULL) printf("null\n");
}

void print_coda(char* s){
    coda* aux=lista.first;
    while(aux){
        if(aux->name==s){
            printf("name: %s\nnum_ref:%d\npid:%d\nfree_space:%d\nindex:%d\n",aux->name,aux->num_ref,aux->pid,aux->free_space,aux->index);
            printf("%s\n",aux->buffer);
        }
        aux=aux->next;
    }
}

