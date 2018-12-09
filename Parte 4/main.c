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
#define FAT_ENTRELACAMENTO 1

void* thread_serv(void *p);
void* thread_clie(void *p);
Pacote_ped* cria_pacote(int op);
Pacote_resp* cria_pacote_resp(char *pr, int op);

int main(){
    Buffer *buf_serv = buffer_inicializa(TAM_BUFF_SERV), *buf_cli[N_CLIENTES];
    int i;
    for(i = 0; i < N_CLIENTES; i++){
        buf_cli[i] = buffer_inicializa(TAM_BUFF_CLIE);
    }
    pthread_t t_serv, t_clie[N_CLIENTES];
    Thread_arg_serv args_serv;
    Thread_arg_clie args_clie[N_CLIENTES];

    inicializa(FAT_ENTRELACAMENTO);
    args_serv.buf_serv = buf_serv;
    args_serv.buf_clie = buf_cli;
    for(i = 0; i < N_CLIENTES; i++){
        args_clie[i].buf = buf_cli[i];
        args_clie[i].buf_serv = buf_serv;
        args_clie[i].num = i;
    }

    pthread_create(&t_serv, NULL, thread_serv, &args_serv);
    for(i = 0; i < N_CLIENTES; i++){
        pthread_create(&(t_clie[i]), NULL, thread_clie, &(args_clie[i]));
    }
    int r = pthread_join(t_serv, NULL);
    for(i = 0; i < N_CLIENTES; i++){
        r = pthread_join(t_clie[i], NULL);
    }
    printf("FIM\n");
}

void* thread_serv(void *p){
    int l = 0;
    while(l < N_CLIENTES){
        Thread_arg_serv *p_arg = (Thread_arg_serv*) p;
        // espera algum pacote_pedido chegar
        Buffer *buf_serv = p_arg->buf_serv;
        Buffer **buf_clie = p_arg->buf_clie;
        int siz = sizeof(Pacote_ped), tam = 0;
        void *p_aux = (void*) malloc(siz);
        printf("\n#thread servidor espera pedido#\n\n");

        buffer_remove(buf_serv, p_aux, siz, &tam);
        Pacote_ped *pacte = (Pacote_ped*) p_aux;

        printf("operacao %d do cliente %d.\n", pacte->op, pacte->id_buf);
        printf("setor %d %d %d\n", pacte->id_setor[0], pacte->id_setor[1], pacte->id_setor[2]);
        if(!pacte->op)
            printf("Escrito no disco: %s\n", pacte->buff);
        // coloca o pedido na fila @@IMPLEMENTAR@@

        // executa o pacote pedido chamando as funcoes do disco
        void* buff = malloc(512);
        char* pr = (char*)buff;
        //leitura
        if(pacte->op){
            entrelacamento(pacte->id_setor, pacte->op, buff);
        }
        //escrita
        else{
            int j;
            for(j = 0; j < strlen(pacte->buff); j++)
                pr[j] = pacte->buff[j];
            entrelacamento(pacte->id_setor, pacte->op, buff);
        }

        // escreve no buffer da thread_cliente correspondente a resposta
        Pacote_resp *pacte_r = cria_pacote_resp(pr, pacte->op);
        int taman = sizeof(Pacote_resp);
        void *p = (void*) pacte_r;
        int r = buffer_insere(buf_clie[pacte->id_buf], p, taman);
        if(!r)
            printf("erro na insercao do serv->clie");
        l++;
    }
    return 0;
}

void* thread_clie(void *p){
    int l = 0;
    while(l < 1){
        Thread_arg_clie *p_arg = (Thread_arg_clie*) p;
        Buffer *buf_serv = p_arg->buf_serv;
        Buffer *buf_clie = p_arg->buf;
        printf("thread cliente %d inicia\n", p_arg->num);

        // manda um pacote pedido para o buffer da thread servidora
        int op = p_arg->num;
        void *p_aux = (void*) cria_pacote(op);
        int taman = sizeof(Pacote_ped);

        int r = buffer_insere(buf_serv, p_aux, taman);
        if(!r)
            printf("Nao inseriu\n");
        // espera a resposta do pedido da thread servidora chegar no seu buffer
        int siz_rem = sizeof(Pacote_resp);
        int tam = 0;
        void *p = (void*) malloc(siz_rem);
        buffer_remove(buf_clie, p, siz_rem, &tam);
        Pacote_resp *resp = (Pacote_resp*) p;
        if(resp->resp){
            printf("operacao realizada com sucesso.\n");
            if(resp->op){
                printf("conteudo lido do disco -> %s\n", resp->buff);
            }
        }
        l++;
    }
    return 0;
}

Pacote_ped* cria_pacote(int buff){
    Pacote_ped *pacte = (Pacote_ped*) malloc(sizeof(Pacote_ped));
    int *p_set = (int*) malloc(sizeof(int)*3);
    p_set[0] = 0;
    p_set[1] = 0;
    p_set[2] = 1;
    pacte->id_setor = p_set;
    pacte->id_buf = buff;
    pacte->op = buff % 2;
    if(!(buff % 2)){
        char *temp = "isso eh o que foi colocado\n";
        int i;
        for(i = 0; i < strlen(temp); i++)
            pacte->buff[i] = temp[i];
    }
    return pacte;
}

Pacote_resp* cria_pacote_resp(char *pr, int op){
    int i;
    Pacote_resp *resp = (Pacote_resp*) malloc(sizeof(Pacote_resp));
    if(op){
        for(i = 0; i < strlen(pr); i++)
            resp->buff[i] = pr[i];
    }
    resp->op = op;
    resp->resp = 1;
    return resp;
}
