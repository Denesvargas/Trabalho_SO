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

    inicializa();
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
        Buffer *buf_serv = p_arg->buf_serv;
        Buffer *buf_clie[N_CLIENTES] = p_arg->buf_clie;
        int siz = sizeof(Pacote_ped), tam = 0;
        void *p_aux = (void*) malloc(siz);
        buffer_remove(buf_serv, p_aux, siz, &tam);
        Pacote_ped pacte = (Pacote_ped) p_aux;
        // coloca o pedido na fila

        // executa o pacote pedido chamando as funcoes do disco
        void* buff = malloc(512);
        char* pr = (char*)buff;
        entrelacamento(pacte.id_setor, pacte.op, buff);
        if(pacte.op)
            printf("%s\n",pr);
        else
            strcpy(pr,"CARALHO");
        // escreve no buffer da thread_cliente correspondente a resposta
        Pacote_resp pacte_r;
        pacte_r.buff = pr;
        pacte_r.resp = 1;
        int taman = sizeof(Pacote_resp);
        void *p = (void*) pacte_r;
        int r = buffer_insere(buf_clie[pacte.id_buf], p, taman);
        if(!r)
            printf("erro na insercao do serv->clie");
        i++;
    }
    return 0;
}

void* thread_clie(void *p){
    int l = 0;
    while(l < 1){
        Thread_arg_clie *p_arg = (Thread_arg_rem*) p;
        Buffer *buf_serv = p_arg->buf_serv;
        Buffer *buf_clie = p_arg->buf;
        Pacote_ped pacte;
        pacte.id_setor = 0;
        pacte.id_buf = 0;
        pacte.op = 0;
        pacte.buff = "tesTando";
        // manda um pacote pedido para o buffer da thread servidora
        void *p_aux = (void*) pacte;
        int taman = sizeof(Pacote_ped);
        int r = buffer_insere(buf_serv, p_aux, taman);
        if(!r)
            printf("Nao inseriu\n");
        // espera a resposta do pedido da thread servidora chegar no seu buffer
        int siz_rem = sizeof(Pacote_resp);
        int tam = 0, r = 0, i;
        void *p_aux = (void*) malloc(siz_rem);
        buffer_remove(buf_clie, p_aux, siz_rem, &tam);
        free(p_aux);
        l++;
    }
    return 0;
}
