#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "buffer.h"

void adiciona(){

}

void remove(){

}

int main(){
    Buffer* buf = buffer_inicializa(100);
    char *teste = "nnnnnnnnnn", *teste2 = "fedcbaa";
    void *p1 = (void*) teste;
    void *p2 = (void*) teste2;
    int s = buffer_insere(buf, p1, strlen(teste));
    buffer_imprime(buf);
    printf("\n");
    s = buffer_insere(buf, p2, strlen(teste2));
    buffer_imprime(buf);
    int tam = 0, i, r;
    void *p = (void*) malloc(6);
    r = buffer_remove(buf, p, 6, &tam);
    char *caralho = (char*) p;
    printf("%d removidos\n", tam);
    for(i = 0; i < 6; i++){
        printf("-%c", caralho[i]);
    }
    printf("-\n");
    r = buffer_remove(buf, p, 7, &tam);
    if(r == 1){
        printf("%d removidos\n", tam);
        char *aux2 = (char*) p;
        for(i = 0; i < 6; i++){
            printf("-%c", aux2[i]);
        }
        printf("\n");
    }
}
