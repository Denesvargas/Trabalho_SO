#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <semaphore.h>
#include <pthread.h>
#include "buffer.h"

struct buffer{
  int cap;
  char* buffer;
  int index_ins, index_rem;
  pthread_mutex_t mutex;
  sem_t sem_ins, sem_rem;
};

Buffer* buffer_inicializa(int cap){
    Buffer* buff = (Buffer*) malloc(sizeof(Buffer*));
    buff->buffer = (char*) malloc(cap);
    buff->cap = cap;
    buff->index_ins = 0;
    buff->index_rem = 0;
    pthread_mutex_init(&(buff->mutex), NULL);
    sem_init(&(buff->sem_ins), 0, 1);
    sem_init(&(buff->sem_rem), 0, 0);
    return buff;
}

void buffer_finaliza(Buffer *buf){
    free(buf->buffer);
    free(buf);
    return;
}

bool buffer_insere(Buffer *buf, void *p, int tam){
    sem_wait(&(buf->sem_ins));
    if(buffer_tam_livre(buf) < tam + 4){
        sem_post(&(buf->sem_ins));
        return 0;
    }
    pthread_mutex_lock(&(buf->mutex));
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
    //printf("Inseriu\n");
    pthread_mutex_unlock(&(buf->mutex));
    sem_post(&(buf->sem_rem));
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
    sem_wait(&(buf->sem_rem));
    if(buf->index_ins == buf->index_rem){
        sem_post(&(buf->sem_ins));
        return 0;
    }
    pthread_mutex_lock(&(buf->mutex));
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
    //printf("removeu\n");
    //buffer_printa(buf);
    pthread_mutex_unlock(&(buf->mutex));
    sem_post(&(buf->sem_ins));
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
