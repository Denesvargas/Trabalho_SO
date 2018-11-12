#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "fila_thread.h"

#define nthread_add 300
#define nthread_rem 300

pthread_mutex_t count_mutex, fila_add_mutex, fila_rem_mutex;
sem_t semaf_empt, semaf_full;

void* adiciona_thr(void *p);
void* remove_thr(void *p);

int main(){
    Buffer* buf = buffer_inicializa(100);
    int i;
    char *teste[] = {"aaaaaaaaaaa","bbbbbbbbbbbbbb","cccccccccccccc","ddddddddddddd"};
    sem_init(&semaf_full, 0 , 0);
    sem_init(&semaf_empt, 0 , 4);
    pthread_t t_add[nthread_add], t_rem[nthread_rem];
    Thread_arg_add args_add[nthread_add];
    Thread_arg_rem args_rem[nthread_rem];
    Fila_add *fila_a = fila_add_cria();
    Fila_rem *fila_r = fila_rem_cria();
    for(i = 0; i < nthread_add; i++){
        args_add[i].aux = teste[i % 4];
        args_add[i].buf = buf;
        args_add[i].mutex = &count_mutex;
        args_add[i].f_mutex = &fila_add_mutex;
        args_add[i].fila = fila_a;
        args_add[i].sem_empt = &semaf_empt;
        args_add[i].sem_full = &semaf_full;
    }
    for(i = 0; i < nthread_rem; i++){
        args_rem[i].tam = 10;
        args_rem[i].buf = buf;
        args_rem[i].mutex = &count_mutex;
        args_rem[i].f_mutex = &fila_rem_mutex;
        args_rem[i].fila = fila_r;
        args_rem[i].sem_empt = &semaf_empt;
        args_rem[i].sem_full = &semaf_full;
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
    Thread_arg_add *p_arg = (Thread_arg_add*) p;
    Buffer *buf = p_arg->buf;
    Fila_add *fila = p_arg->fila;
    pthread_mutex_t *mutex_temp = p_arg->mutex;
    pthread_mutex_lock(p_arg->f_mutex);
    fila_add_ins(fila, p_arg);                       // adiciona na fila de execuçao
    pthread_mutex_unlock(p_arg->f_mutex);

    sem_wait(p_arg->sem_empt);
    pthread_mutex_lock(mutex_temp);
    Thread_arg_add *args_add = fila_add_del(fila);
    char *aux = args_add->aux;
    void *p_aux = (void*) aux;
    int tam = strlen(aux);
    buffer_insere(buf, p_aux, tam);
    sem_post(p_arg->sem_full);
    /*do{
        resp = buffer_ins_verf(buf, size_next);
        if(resp){

        }
        else{
            //unlock rem -- desbloqueia todos os que removem do buffer
            //desbloqueia o acesso geral ao buffer
            //lock add  -- bloqueia todos os que adicionam no buffer, inclusive essa thread com thread condition
            //lock buff -- bloqueia o acesso geral ao buffer
        }
    }while(resp == 0);*/
                                            // implementar bloqueio caso cheio
    pthread_mutex_unlock(mutex_temp);
    return 0;
}

void* remove_thr(void *p){
    Thread_arg_rem *p_arg = (Thread_arg_rem*) p;
    Buffer *buf = p_arg->buf;
    pthread_mutex_t *mutex_temp = p_arg->mutex;
    Fila_rem *fila = p_arg->fila;
    pthread_mutex_lock(p_arg->f_mutex);
    fila_rem_ins(p_arg->fila, p_arg);                       // adiciona na fila de remocao
    pthread_mutex_unlock(p_arg->f_mutex);

    sem_wait(p_arg->sem_full);
    pthread_mutex_lock(mutex_temp);                         // implementar bloqueio caso vazio
    Thread_arg_rem *args_rem = fila_rem_del(fila);
    int siz_rem = p_arg->tam;
    int tam = 0, r = 0, i;
    void *p_aux = (void*) malloc(siz_rem);
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
    sem_post(p_arg->sem_empt);
    pthread_mutex_unlock(mutex_temp);
    return 0;
}
