#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "fila_thread.h"

struct no_add{
    Ins_arg *call;
    No_add* prox;
};

struct fila_add{
    No_add* ini;
};

Fila_add* fila_add_cria(){
    Fila_add* f = (Fila_add*) malloc(sizeof(Fila_add));
    f->ini = NULL;
    return f;
}

void fila_add_ins(Fila_add *fila, void *p, int tam){
    No_add *novo = (No_add*) malloc(sizeof(No_add));
    Ins_arg *ins_arg = (Ins_arg*) malloc(sizeof(Ins_arg));
    ins_arg->p = p;
    ins_arg->tam = tam;
    novo->call = ins_arg;
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

Ins_arg* fila_add_del(Fila_add *fila){
    if(fila->ini != NULL){
        No_add *temp = fila->ini;
        Ins_arg *aux = fila->ini->call;
        fila->ini = fila->ini->prox;
        free(temp);
        return aux;
    }
    else
        return NULL;
}

int fila_add_vazia(Fila_add *fila){
    return (fila->ini == NULL);
}

Fila_rem* fila_rem_cria(){
    Fila_rem* f = (Fila_rem*) malloc(sizeof(Fila_rem));
    f->ini = NULL;
    return f;
}

void fila_rem_ins(Fila_rem *fila, void *p, int cap, int *tam){
    No_rem *novo = (No_rem*) malloc(sizeof(No_rem));
    Rem_arg *rem_arg = (Rem_arg*) malloc(sizeof(Rem_arg));
    rem_arg->p = p;
    rem_arg->cap = cap;
    rem_arg->tam = tam;
    novo->call = rem_arg;
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

Rem_arg* fila_rem_del(Fila_rem *fila){
    if(fila->ini != NULL){
        No_rem *temp = fila->ini;
        Rem_arg *aux = fila->ini->call;
        fila->ini = fila->ini->prox;
        free(temp);
        return aux;
    }
    else
        return NULL;
}

int fila_rem_vazia(Fila_rem *fila){
    return (fila->ini == NULL);
}

