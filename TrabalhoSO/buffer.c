#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

Buffer* buffer_inicializa(int cap){
    Buffer* buff = (Buffer*) malloc(sizeof(Buffer*));
    buff->buffer = (char*) malloc(cap);
    buff->cap = cap;
    buff->index_ins = 0;
    buff->index_rem = 0;
    return buff;
}

void buffer_finaliza(Buffer *buf){
    free(buf->buffer);
    free(buf);
    return;
}

bool buffer_insere(Buffer *buf, void *p, int tam){
    if(tam <= 0)
        return 0;
    char* aux = (char*) p;
    int j;
    for(j = 0; buf->index_ins < buf->cap && j < tam; j++){
        buf->buffer[buf->index_ins++] = aux[j];
    }
    buf->buffer[buf->index_ins++] = 0;
    return 1;
}

void buffer_imprime(Buffer *buf){
    printf("Conteudo, %d: \n", buf->cap);
    for(int i = 0; i < buf->index_ins; i++){
        printf("%c ",buf->buffer[i]);
    }
    printf("\n");
}

bool buffer_remove(Buffer *buf, void *p, int cap, int *tam){
    if(tam <= 0)
        return 0;
    char *aux = (char*) p;
    int i;
    for(i = 0; buf->buffer[buf->index_rem] != 0; i++){
        if(i < cap)
            aux[i] = buf->buffer[buf->index_rem++];
        else
            buf->index_rem++;
    }
    *tam = i;
}
