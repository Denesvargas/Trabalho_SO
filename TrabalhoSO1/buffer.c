#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "buffer.h"

char* dataheader(int tam){
    int i;
    char* strtam = malloc(sizeof(char) * sizeof(int) * 4 + 1);
    itoa(tam, strtam, 2);
    char* saida = malloc(sizeof(char) * sizeof(int) * 8 + 1);
    sprintf(saida, "%032s", strtam);
    return saida;
}

Buffer* buffer_inicializa(int cap){
    Buffer* buff = (Buffer*) malloc(sizeof(Buffer*));
    buff->buffer = (char*) malloc(cap);
    buff->cap = cap;
    buff->index_ins = 97;
    buff->index_rem = 97;
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
    char* data = (char*) malloc(4);
    data = (char*) realloc(data, 4 + tam);
    int k, j , i;

    data[0] = tam;

    for(k = 4, i = 0; i < tam; k++, i++){
        data[k] = aux[i];
    }

    for(i = buf->index_ins, j = 0; buf->index_ins < buf->cap && j < tam+4; j++, i++){
        buf->buffer[i % buf->cap] = data[j];
    }

    buf->index_ins = i % buf->cap;
    return 1;
}

void buffer_imprime(Buffer *buf){
    for(int i = 0; i < buf->index_ins; i++){
        printf("%c ", buf->buffer[i]);
    }
    printf("\n");
    for(int i = 0; i < buf->index_ins; i++){
        printf("%d ", buf->buffer[i]);
    }
    printf("\n");
}

bool buffer_remove(Buffer *buf, void *p, int cap, int *tam){
    if(buf->index_ins == buf->index_rem)
        return 0;
    char* aux = (char*) p;
    int i, j, k, m;

    int siz = buf->buffer[buf->index_rem];

    printf("\n\n-%d-\n\n",siz);

    buf->index_rem += 4;

    for(i = 0, k = buf->index_rem; i < siz; i++){
        if(i < cap){
            aux[i] = buf->buffer[(i + k) % buf->cap];
        }
        buf->index_rem = (i + k) % buf->cap;
    }
    buf->index_rem = (i + k) % buf->cap;
    *tam = siz;
    return 1;
}


/*bool buffer_remove(Buffer *buf, void *pointer, int cap, int *tam){
    if(buf->index_ins == buf->index_rem)
        return 0;
    char *aux = (char*) pointer;
    int i, j, k, size = 0;
    char* strtam2 = malloc(sizeof(char) * sizeof(int) * 8 + 1);
    for(j = 0; j < 32; j++){
        strtam2[j] = buf->buffer[buf->index_rem % buf->cap];
        buf->index_rem++;
    }
    for(j = 31, k = 0; j >= 0; j--, k++){
        if(strtam2[j] == '1')
            size += pow(2, k);
    }
    for(i = buf->index_rem, k = buf->index_rem; i < k + size; i++){
        if(i < cap + k){
            aux[i] = buf->buffer[i % buf->cap];
            printf("-%c-", aux[i]);
        }
        buf->index_rem = i % buf->cap;
    }
    *tam = size;
    free(strtam2);
    return 1;
}*/
