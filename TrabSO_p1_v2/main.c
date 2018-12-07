#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "fila_thread.h"

#define nthread_add 1
#define nthread_rem 1

void* adiciona_thr(void *p);
void* remove_thr(void *p);

int main(){
    Buffer* buf = buffer_inicializa(1000);
    int i;
    char *teste[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa","bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb","cccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccccc","dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd"};

    pthread_t t_add[nthread_add], t_rem[nthread_rem];
    Thread_arg_add args_add[nthread_add];
    Thread_arg_rem args_rem[nthread_rem];
    for(i = 0; i < nthread_add; i++){
        args_add[i].aux = teste[i % 4];
        args_add[i].buf = buf;
        args_add[i].num = i;
    }
    for(i = 0; i < nthread_rem; i++){
        args_rem[i].tam = 10;
        args_rem[i].buf = buf;
        args_rem[i].num = i;
    }
    time_t tempo_ini, tempo_fim;
    tempo_ini = time(NULL);
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
    tempo_fim = time(NULL);
    printf("FIM\n");
    float diff = difftime(tempo_fim, tempo_ini);
    printf("Tempo total %lf.\n", diff);
    buffer_imprime(buf);
    buffer_printa(buf);
}

void* adiciona_thr(void *p){
    int i = 0;
    while(i < 10){
        Thread_arg_add *p_arg = (Thread_arg_add*) p;
        Buffer *buf = p_arg->buf;

        /*while(buffer_ins_verf(buf, fila_siz_next(fila), fila, strlen(p_arg->aux))){
            fila_add_ins(fila, p_arg);
            pthread_cond_wait(p_arg->cond, mutex_temp);
        }
        Thread_arg_add *args_add;
        if(fila_add_vazia(fila)){
            args_add = p_arg;
        }
        else{
            args_add = fila_add_del(fila);
        }*/
        char *aux = p_arg->aux;
        void *p_aux = (void*) aux;
        int tam = strlen(aux);
        int r = buffer_insere(buf, p_aux, tam);
        /*if(!r)
            printf("\n\nNao adicionou\n\n");
        if(r){
            printf("adicionou no buffer -> %d de tam %d\n", p_arg->num, tam);
            buffer_printa(buf);
        }
        else
            printf("nao adicionou\n");*/
        i++;
    }
    return 0;
}




void* remove_thr(void *p){
    int l = 0;
    while(l < 10){
        Thread_arg_rem *p_arg = (Thread_arg_rem*) p;
        //printf("\nthread %d \n", p_arg->num);
        Buffer *buf = p_arg->buf;

        /*while(buffer_rem_verf(buf)){
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
        }*/
        //era pra ir aqui o unlock do mutex_temp
        int siz_rem = p_arg->tam;
        int tam = 0, r = 0, i;
        void *p_aux = (void*) malloc(siz_rem);
        r = buffer_remove(buf, p_aux, siz_rem, &tam);
        if(!r)
            printf("\n\n\nNao removeu\n\n\n\n\n\n");
        /*if(r){
            char *caralho = (char*) p_aux;
            printf("%d removidos > ", tam);
            if(siz_rem > tam)
                siz_rem = tam;
            for(i = 0; i < siz_rem; i++){
                printf("-%c", caralho[i]);
            }
            printf("-CU-\n");
            printf("thread %d \n", p_arg->num);
        }
        else
            printf("\n\nNao removeu\n\n");*/
        l++;
    }
    return 0;
}
