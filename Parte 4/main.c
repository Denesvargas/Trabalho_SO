#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "fila_thread.h"

#define N_CLIENTES 2
#define TAM_BUFF_SERV 10000
#define TAM_BUFF_CLIE 2000

void* adiciona_thr(void *p);
void* remove_thr(void *p);

int main(){
    Buffer *buf_serv = buffer_inicializa(TAM_BUFF_SERV), *buf_cli[N_CLIENTES];
    int i;
    for(i = 0; i < N_CLIENTES; i++){
        buf_cli[i] = buffer_inicializa(TAM_BUFF_CLIE);
    }
    pthread_t t_serv, t_clie[N_CLIENTES];
    Thread_arg_serv args_serv;
    Thread_arg_clie args_clie[N_CLIENTES];

    args_serv.buf_serv = buf_serv;
    args_serv.buf_clie = buf_cli;
    for(i = 0; i < N_CLIENTES; i++){
        args_clie[i].buf = buf_cli[i];
        args_clie[i].buf_serv = buf_serv;
    }
    clock_t tempo_ini, tempo_fim;
    tempo_ini = clock();

    pthread_create(&t_serv, NULL, thread_serv, &args_serv);
    for(i = 0; i < N_CLIENTES; i++){
        pthread_create(&(t_clie[i]), NULL, thread_clie, &(args_clie[i]));
    }
    int r = pthread_join(t_serv, NULL);
    for(i = 0; i < N_CLIENTES; i++){
        r = pthread_join(t_clie[i], NULL);
    }
    tempo_fim = clock();
    printf("FIM\n");
    int tempo = (tempo_fim - tempo_ini)*1000/CLOCKS_PER_SEC;
    printf("Tempo total %d.\n", tempo);
}

void* thread_serv(void *p){
    int i = 0;
    while(i < 1){
        Thread_arg_serv *p_arg = (Thread_arg_add*) p;
        // espera algum pacote_pedido chegar

        // executa o pacote pedido chamando as funcoes do disco

        // escreve no buffer da thread_cliente correspondente a resposta

    }
    return 0;
}

void* thread_clie(void *p){
    int l = 0;
    while(l < 1){
        Thread_arg_clie *p_arg = (Thread_arg_rem*) p;

        // manda um pacote pedido para o buffer da thread servidora

        // espera a resposta do pedido da thread servidora chegar no seu buffer

    }
    return 0;
}
