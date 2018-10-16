#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "buffer.h"

#define nthread_add 1330
#define nthread_rem 1100

pthread_mutex_t count_mutex;

void* adiciona_thr(void *p);
void* remove_thr(void *p);

typedef struct{
    Buffer *buf;
    pthread_mutex_t *mutex;
    char *aux;
}thread_arg_add;

typedef struct{
    Buffer *buf;
    pthread_mutex_t *mutex;
    int size;
}thread_arg_rem;

int main(){
    Buffer* buf = buffer_inicializa(100);
    int i;
    char *teste[] = {"aaaaaaaaaaa","bbbbbbbbbbbbbb","cccccccccccccc","ddddddddddddd"};
    pthread_t t_add[nthread_add], t_rem[nthread_rem];
    thread_arg_add args_add[nthread_add];
    thread_arg_rem args_rem[nthread_rem];
    for(i = 0; i < nthread_add; i++){
        args_add[i].aux = teste[i % 4];
        args_add[i].buf = buf;
        args_add[i].mutex = &count_mutex;
    }
    for(i = 0; i < nthread_rem; i++){
        args_rem[i].size = 10;
        args_rem[i].buf = buf;
        args_rem[i].mutex = &count_mutex;
    }
    pthread_mutex_init(&count_mutex, NULL);
    for(i = 0; i < nthread_add; i++){
        pthread_create(&(t_add[i]), NULL, adiciona_thr, &(args_add[i]));
    }
    for(i = 0; i < nthread_rem; i++){
        pthread_create(&(t_rem[i]), NULL, remove_thr, &(args_rem[i]));
    }
    for(i = 0; i < nthread_add; i++){
        int r = pthread_join(t_add[i], NULL);
         r = pthread_join(t_rem[i], NULL);
    }
    printf("FIM\n");
    buffer_imprime(buf);
}

void* adiciona_thr(void *p){
    thread_arg_add *p_arg = (thread_arg_add*) p;
    Buffer *buf = p_arg->buf;
    char *aux = p_arg->aux;
    pthread_mutex_t *mutex_temp = p_arg->mutex;
    void *p_aux = (void*) aux;
    int tam = strlen(aux);
    pthread_mutex_lock(mutex_temp);
    int r = buffer_insere(buf, p_aux, tam);
    if(!r)
        printf("Nao adicionou no buffer\n");
    else{
        buffer_imprime(buf);
        printf("\n");
    }
    pthread_mutex_unlock(mutex_temp);
    return 0;
}

void* remove_thr(void *p){
    thread_arg_rem *p_arg = (thread_arg_rem*) p;
    Buffer *buf = p_arg->buf;
    int siz_rem =p_arg->size;
    int tam = 0, r = 0, i;
    pthread_mutex_t *mutex_temp = p_arg->mutex;
    void *p_aux = (void*) malloc(siz_rem);
    pthread_mutex_lock(mutex_temp);
    r = buffer_remove(buf, p_aux, siz_rem, &tam);
    if(r){
        char *caralho = (char*) p_aux;
        printf("%d removidos\n", tam);
        if(siz_rem > tam)
            siz_rem = tam;
        for(i = 0; i < siz_rem; i++){
            printf("-%c", caralho[i]);
        }
        printf(" -> %d foram pedidos\n", i);
    }
    else
        printf("Nao removeu");
    pthread_mutex_unlock(mutex_temp);
}
