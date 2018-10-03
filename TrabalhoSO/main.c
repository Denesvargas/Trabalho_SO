#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "buffer.h"

int main(){
    Buffer* buf = buffer_inicializa(10000);
    char* teste1 = "abcdef", *teste2 = "bbbbbbbb";
    buffer_insere(buf, teste1, strlen(teste1));
    buffer_insere(buf, teste2, strlen(teste2));
    buffer_imprime(buf);
    int tam = 0, i;
    void *p = (void*) malloc(6);
    int r = buffer_remove(buf, p, 6, &tam);
    printf("%d removidos", tam);
    char *aux = (char*) p;
    for(i = 0; i < 7; i++){
        printf("%c", aux[i]);
    }
    printf("\n");
    int r = buffer_remove(buf, p, 6, &tam);
    printf("%d removidos", tam);
    char *aux = (char*) p;
    for(i = 0; i < 7; i++){
        printf("%c", aux[i]);
    }
    printf("\n");
}
