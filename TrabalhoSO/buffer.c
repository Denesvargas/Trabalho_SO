#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"

Buffer* buffer_inicializa(int cap){
    Buffer* buff = (Buffer*) malloc(sizeof(Buffer*));
    buff->buffer = (char*) malloc(cap);
    buff->index = 0;
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
    buf->buffer[buf->index] = *aux;
    return 1;
}

void buffer_imprime(Buffer *buf){
    printf("Conteudo, %d: \n", buf->cap);
    for(int i=0; i< buf->cap; i++){
	printf("%c ",buf->buffer[i]);
    }
    printf("\n");
}
