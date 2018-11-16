#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "buffer.h"
#include "fila_thread.h"

struct no_add{
    Thread_arg_add *call;
    No_add* prox;
};

struct no_rem{
    Thread_arg_rem *call;
    No_rem* prox;
};

struct fila_add{
    No_add* ini;
};

struct fila_rem{
    No_rem* ini;
};

Fila_add* fila_add_cria(){
    Fila_add* f = (Fila_add*) malloc(sizeof(Fila_add));
    f->ini = NULL;
    return f;
}

Fila_rem* fila_rem_cria(){
    Fila_rem* f = (Fila_rem*) malloc(sizeof(Fila_rem));
    f->ini = NULL;
    return f;
}

void fila_add_ins(Fila_add *fila, Thread_arg_add *thread_arg){
    No_add *novo = (No_add*) malloc(sizeof(No_add));
    novo->call = thread_arg;
    novo->prox = NULL;
    if(fila->ini == NULL){
        fila->ini = novo;
    }
    else{
        No_add *temp = fila->ini;
        while(temp->prox != NULL){
             temp = temp->prox;
        }
        temp->prox = novo;
    }
}

void fila_rem_ins(Fila_rem *fila, Thread_arg_rem *thread_arg){
    No_rem *novo = (No_rem*) malloc(sizeof(No_rem));
    novo->call = thread_arg;
    novo->prox = NULL;
    if(fila->ini == NULL){
        fila->ini = novo;
    }
    else{
        No_rem *temp = fila->ini;
        while(temp->prox != NULL){
             temp = temp->prox;
        }
        temp->prox = novo;
    }
}

Thread_arg_add* fila_add_del(Fila_add *fila){
    if(fila->ini != NULL){
        Thread_arg_add *aux = fila->ini->call;
        fila->ini = fila->ini->prox;
        return aux;
    }
    else
        return NULL;
}

Thread_arg_rem* fila_rem_del(Fila_rem *fila){
    if(fila->ini != NULL){
        Thread_arg_rem *aux = fila->ini->call;
        fila->ini = fila->ini->prox;
        return aux;
    }
    else
        return NULL;
}

int fila_siz_next(Fila_add *fila){
    if(fila->ini != NULL)
        return strlen(fila->ini->call->aux);
    return -1;
}

int fila_add_vazia(Fila_add *fila){
    if(fila->ini == NULL)
        return 1;
    else
        return 0;
}

int fila_rem_vazia(Fila_rem *fila){
    if(fila->ini == NULL)
        return 1;
    else
        return 0;
}

int buffer_ins_verf(Buffer *buf, int tam, Fila_add *fila, int tam2){
    int livre = buffer_tam_livre(buf);
    if(fila_add_vazia(fila))
        tam = tam2;
    if(tam > livre)
        return 1;             // nao cabe no buffer
    else
        return 0;
}
