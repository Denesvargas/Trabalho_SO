#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

Buffer* buffer_inicializa(int cap){
    Buffer* buff = (Buffer*) malloc(sizeof(Buffer*));
    buff->buffer = (char*) malloc(cap);
    buff->cap = cap;
    buff->index = 0;
    return buff;
}

void buffer_finaliza(Buffer *buf){
    free(buf->buffer);
    free(buf);
    return;
}

bool buffer_insere(Buffer *buf, void *p, int tam){
    printf("cuzao\n");
    if(tam <= 0)
        return 0;
    char* aux = (char*) p;
    int i, j;
    for(j = 0; buf->index < buf->cap && j <= tam; j++){
        buf->buffer[buf->index++] = aux[j];
    }
    printf("cuzao");
    return 1;
}

void buffer_imprime(Buffer *buf){
    printf("Conteudo, %d: \n", buf->cap);
    for(int i = 0; i < buf->index; i++){
        printf("%c ",buf->buffer[i]);
    }
    printf("\n");
}
