#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include "fila_thread.h"

struct buffer{
  int cap;
  char* buffer;
  int index_ins, index_rem;
  pthread_mutex_t mutex;
  Fila_add *fila_ad;
  Fila_rem *fila_re;
  pthread_cond_t cond;
  pthread_cond_t cond2;
  pthread_condattr_t cattr;
};

Buffer* buffer_inicializa(int cap){
    Buffer* buff = (Buffer*) malloc(sizeof(Buffer));
    pthread_condattr_setpshared(&(buff->cattr), PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&(buff->mutex), NULL);
    pthread_cond_init(&(buff->cond), &(buff->cattr));
    pthread_cond_init(&(buff->cond2), &(buff->cattr));
    buff->buffer = (char*) malloc(cap);
    buff->cap = cap;
    buff->index_ins = 0;
    buff->index_rem = 0;
    buff->fila_ad = fila_add_cria();
    buff->fila_re = fila_rem_cria();
    return buff;
}


void buffer_finaliza(Buffer *buf){
    free(buf->buffer);
    free(buf);
    return;
}

bool buffer_insere(Buffer *buf, void *p, int tam){
    pthread_mutex_lock(&(buf->mutex));
    while(buffer_tam_livre(buf) < tam + 4){
        fila_add_ins(buf->fila_ad, p, tam);
        pthread_cond_wait(&(buf->cond2), &(buf->mutex));
    }
    if(!fila_add_vazia(buf->fila_ad)){
        Ins_arg *arg = fila_add_del(buf->fila_ad);
        if(arg->p != p){
            fila_add_ins(buf->fila_ad, p, tam);
            p = arg->p;
            tam = arg->tam;
        }
        free(arg);
    }
    char* aux = (char*) p;
    unsigned char* data = (char*) malloc(4 + tam);
    int k, j , i;
    // Cria um vetor void do tamanho do header;
    void* pv = malloc (4);
    // Transforma ele em um vetor de int com 1 posição;
    int* pi = (int*)pv;
    // Coloca o tamanho dentro desse vetor void(int);
    *pi = tam;
    // Transforma o vetor void para char;
    char* pp = (char*)pv;
    // Poe o valor que ta dividido em chars no buffer;
    for(int z=0; z<4;z++){
        data[z] = pp[z];
    }
    // STRCAT não é o melhor metodo, da pra usar um for i 0:4 passando um por vez
    for(k = 4, i = 0; i < tam; k++, i++){
        data[k] = aux[i];
    }
    if(buf->cap - buf->index_ins < 4){
        buf->index_ins = 0;
    }
    for(i = buf->index_ins, j = 0; buf->index_ins < buf->cap && j <= tam + 4; j++, i++){
        buf->buffer[i % buf->cap] = data[j];
        k = i;
    }
    free(data);
    free(pv);
    k = k % buf->cap;
    buf->index_ins = k;
    pthread_cond_signal(&(buf->cond));
    pthread_mutex_unlock(&(buf->mutex));
    return 1;
}

void buffer_imprime(Buffer *buf){
    int j, i = buf->index_rem, header;

    void* pv = malloc(4);
    char* pc = (char*)pv;
    int* pi = (int*)pv;

    if(buf->index_ins == buf->index_rem)
        printf("Buffer vazio\n");
    else{
        while (i != buf->index_ins) {
            if(buf->cap - buf->index_rem < 4){
                for (int n=0; n<4;n++)
                    pc[n] = buf->buffer[n];
                header = pi[0];
            }
            else{
                for (int n=0; n<4;n++)
                    pc[n] = buf->buffer[i + n];
                header = pi[0];
            }
            printf("%d  -> ", header);
            i += 4;                                    // arrumar header
            for (j = 0; j < header; j++)
                printf("%c", buf->buffer[(i+j) % buf->cap]);
            printf("\n");
            i= (i + header) % buf->cap;
        }
    }
    /*for(int i = 0; i < buf->index_ins; i++){
        printf("%c %d", buf->buffer[i], i);             erro do print 13
    }
    printf("\n");*/
}

bool buffer_remove(Buffer *buf, void *p, int cap, int *tam){
    pthread_mutex_lock(&(buf->mutex));
    while(buf->index_ins == buf->index_rem){
        //fila_rem_ins(buf->fila_re, p, cap, tam);
        //printf("\n#################################################################\n");
        pthread_cond_wait(&(buf->cond), &(buf->mutex));
    }
    /*if(!fila_rem_vazia(buf->fila_re)){
        Rem_arg *temp = fila_rem_del(buf->fila_re);
        if(temp->p != p){
            fila_rem_ins(buf->fila_re, p, cap, tam);
            p = temp->p;
            cap = temp->cap;
            tam = temp->tam;
        }
        free(temp);
    }*/
    char* aux = (char*) p;
    int i, k;
    if(buf->cap - buf->index_rem < 4)
        buf->index_rem = 0;

    //int siz = buf->buffer[buf->index_rem];
    void* pv = malloc(4);
    char* pc = (char*)pv;
    int* pi = (int*)pv;
    // passa os itens do header pro vetor void
    for (int n=0; n<4;n++)
        pc[n] = buf->buffer[buf->index_rem + n];
    // passa o unico inteiro do vetor void para a variavel tamanho2
    int siz = pi[0];
    buf->index_rem += 4;
    for(i = 0, k = buf->index_rem; i < siz; i++){
        if(i < cap){
            aux[i] = buf->buffer[(i + k) % buf->cap];
        }
        buf->index_rem = (i + k) % buf->cap;
    }
    buf->index_rem = (i + k) % buf->cap;
    free(pv);
    pthread_mutex_unlock(&(buf->mutex));
    pthread_cond_signal(&(buf->cond2));
    *tam = siz;
    return 1;
}

int buffer_tam_livre(Buffer *buf){
    int livre = 0;
    if(buf->index_ins == buf->index_rem)
        livre = buf->cap - 4;
    else if(buf->index_ins > buf->index_rem)
        livre = (buf->cap - (buf->index_ins - buf->index_rem)) - 4;
    else if(buf->index_ins < buf->index_rem)
        livre = buf->index_rem - buf->index_ins - 4;
    return livre;
}

int buffer_rem_verf(Buffer *buf){
    if(buf->index_ins == buf->index_rem)
        return 1;             // ta vazio
    else
        return 0;
}

void buffer_printa(Buffer *buf){
    printf("%d %d.\n", buf->index_ins, buf->index_rem);
}
