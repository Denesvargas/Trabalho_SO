#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "fila_thread.h"

#define nthread_add 10
#define nthread_rem 10

pthread_mutex_t count_mutex, fila_add_mutex, fila_rem_mutex;
pthread_cond_t cond, cond2;

void* adiciona_thr(void *p);
void* remove_thr(void *p);

int main(){
    Buffer* buf = buffer_inicializa(100);
    int i;
    char *teste[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaa","bbbbbbbbbbbbbb","cccccccccccccc","ddddddddddddd"};

    pthread_t t_add[nthread_add], t_rem[nthread_rem];
    Thread_arg_add args_add[nthread_add];
    Thread_arg_rem args_rem[nthread_rem];
    Fila_add *fila_a = fila_add_cria();
    Fila_rem *fila_r = fila_rem_cria();
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&cond2, NULL);
    for(i = 0; i < nthread_add; i++){
        args_add[i].aux = teste[i % 4];
        args_add[i].buf = buf;
        args_add[i].mutex = &count_mutex;
        args_add[i].f_mutex = &fila_add_mutex;
        args_add[i].fila = fila_a;
        args_add[i].cond = &cond;
        args_add[i].cond2 = &cond2;
        args_add[i].num = i;
    }
    for(i = 0; i < nthread_rem; i++){
        args_rem[i].tam = 10;
        args_rem[i].buf = buf;
        args_rem[i].mutex = &count_mutex;
        args_rem[i].f_mutex = &fila_rem_mutex;
        args_rem[i].fila = fila_r;
        args_rem[i].cond = &cond;
        args_rem[i].cond2 = &cond2;
        args_rem[i].num = i;
    }
    pthread_mutex_init(&count_mutex, NULL);
    pthread_mutex_init(&fila_add_mutex, NULL);
    pthread_mutex_init(&fila_rem_mutex, NULL);
    printf("inicio\n");
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
    //buffer_imprime(buf);
    buffer_printa(buf);
}

void* adiciona_thr(void *p){
    Thread_arg_add *p_arg = (Thread_arg_add*) p;
    Buffer *buf = p_arg->buf;
    Fila_add *fila = p_arg->fila;
    pthread_mutex_t *mutex_temp = p_arg->mutex;

    pthread_mutex_lock(mutex_temp);
    while(buffer_ins_verf(buf, fila_siz_next(fila), fila, strlen(p_arg->aux))){
        fila_add_ins(fila, p_arg);
        pthread_cond_wait(p_arg->cond, mutex_temp);
    }
    Thread_arg_add *args_add;
    if(fila_add_vazia(fila)){
        args_add = p_arg;
    }
    else{
        args_add = fila_add_del(fila);
    }
    char *aux = args_add->aux;
    void *p_aux = (void*) aux;
    int tam = strlen(aux);
    int r = buffer_insere(buf, p_aux, tam);
    if(r){
        printf("adicionou no buffer -> %d de tam %d\n", p_arg->num, tam);
        buffer_printa(buf);
    }
    else
        printf("nao adicionou\n");
    pthread_mutex_unlock(mutex_temp);
    pthread_cond_signal(p_arg->cond2);
    return 0;
}




void* remove_thr(void *p){
    Thread_arg_rem *p_arg = (Thread_arg_rem*) p;
    Buffer *buf = p_arg->buf;
    pthread_mutex_t *mutex_temp = p_arg->mutex;
    Fila_rem *fila = p_arg->fila;

    pthread_mutex_lock(mutex_temp);
    while(buffer_rem_verf(buf)){
        fila_rem_ins(fila, p_arg);
        pthread_cond_wait(p_arg->cond2, mutex_temp);
    }
    Thread_arg_rem *args_rem;
    if(fila_rem_vazia(fila)){
        args_rem = p_arg;
    }
    else{
        fila_rem_ins(p_arg->fila, p_arg);
        args_rem = fila_rem_del(fila);
    }
    int siz_rem = p_arg->tam;
    int tam = 0, r = 0, i;
    void *p_aux = (void*) malloc(siz_rem);
    r = buffer_remove(buf, p_aux, siz_rem, &tam);
    if(r){
        char *caralho = (char*) p_aux;
        printf("%d removidos > ", tam);
        if(siz_rem > tam)
            siz_rem = tam;
        for(i = 0; i < siz_rem; i++){
            printf("-%c", caralho[i]);
        }
        printf("\n -> %d foram pedidos\n", i);
    }
    else
        printf("Nao removeu");
    pthread_mutex_unlock(mutex_temp);
    pthread_cond_signal(p_arg->cond);
    return 0;
}
