#include<stdio.h>
#include<stdlib.h>
#include"fila_serv.h"

Fila_serv* cria_fila_serv(){
    Fila_serv* fs = (Fila_serv*)malloc(sizeof(Fila_serv));
    fs->no = NULL;
    fs->direction = 0;
    fs->current_track = 40;
    return fs;
}

No_serv* last_node(No_serv* no){
    if(no->prox == NULL) return no;
    return last_node(no->prox);
}

No_serv* cria_no_serv(Pacote_ped* ped){
    No_serv* new = (No_serv*)malloc(sizeof(No_serv));
    new->pedido = ped;
    new->prox = NULL;
    return new;
}

void fila_serv_add(Fila_serv* fs, No_serv* no){
    if(fs == NULL) return;
    if(fs->no == NULL){
        fs->no = no;
    }
    else{
        No_serv* last = last_node(fs->no);
        if(last == NULL) return;
        last->prox = no;
    }
}

No_serv* fila_serv_fifo(Fila_serv* fs){
    if(fs == NULL)
        return NULL;
    if(fs->no == NULL)
        return NULL;
    No_serv* New = fs->no;
    fs->no = fs->no->prox;
    return New;
}

int fila_vazia(Fila_serv* fs){
    if(fs->no == NULL)
        return 1;
    return 0;
}

void printa_fila_s(No_serv* ss){
    if(ss == NULL) return;
    printf(" =%d=\n",ss->pedido->id_buf);
    return printa_fila_s(ss->prox);
}


No_serv* fila_serv_elev(Fila_serv* fs){
    if(fs == NULL)
        return NULL;
    if(fs->no == NULL)
        return NULL;
    No_serv* curr = fs->no, *best = NULL, *pre_best = NULL, *pre_curr = NULL;
    while(curr != NULL)
    {
        int dist;
        if(fs->direction == 1){
            dist = (curr->pedido->id_setor[0] - fs->current_track);
            if(best == NULL && dist >= 0){
                pre_best = pre_curr;
                best = curr;}
            else if(best == NULL){}
            else if(dist < (best->pedido->id_setor[0] - fs->current_track) && dist >= 0){
                pre_best = pre_curr;
                best = curr;}
        }
        else{
            dist = (curr->pedido->id_setor[0] - fs->current_track);
            if(best == NULL && dist <= 0){
                pre_best = pre_curr;
                best = curr;}
            else if(best == NULL){}
            else if(dist > (best->pedido->id_setor[0] - fs->current_track) && dist <= 0){
                pre_best = pre_curr;
                best = curr;}
        }
        pre_curr = curr;
        curr = curr->prox;
        if(curr == NULL && best == NULL){
            curr = fs->no;
            pre_curr = NULL;
            fs->direction = fs->direction? 0 : 1;
        }
    }
    No_serv* New = best;
    if(pre_best == NULL)
        fs->no = best->prox;
    else
        pre_best->prox = best->prox;
    fs->current_track = New->pedido->id_setor[0];
    return New;
}
