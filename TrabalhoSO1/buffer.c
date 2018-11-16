#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "buffer.h"

struct buffer{
  int cap;
  char* buffer;
  int index_ins, index_rem;
};

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

char* dataheader(int tam){
    int i;
    char* strtam = malloc(sizeof(char) * sizeof(int) * 4 + 1);
    itoa(tam, strtam, 2);
    char* saida = malloc(sizeof(char) * sizeof(int) * 8 + 1);
    sprintf(saida, "%032s", strtam);
    return saida;
}

bool buffer_insere(Buffer *buf, void *p, int tam){
    if(tam <= 0)
        return 0;
    if(buf->index_ins > buf->index_rem){
        if(buf->cap - (buf->index_ins - buf->index_rem) < tam + 4)
            return 0;
    }
    else if(buf->index_ins < buf->index_rem){
        if(buf->index_rem - buf->index_ins < tam + 4)
            return 0;
    }
    char* aux = (char*) p;
    char* data = (char*) malloc(4 + tam);
    int k, j , i;
    data[0] = tam;
    for(k = 4, i = 0; i < tam; k++, i++){
        data[k] = aux[i];
    }
    if(buf->cap - buf->index_ins < 4){
        buf->index_ins = 0;
    }
    for(i = buf->index_ins, j = 0; buf->index_ins < buf->cap && j <= tam + 4; j++, i++){
        buf->buffer[i % buf->cap] = data[j];
        k = i;
    }
    k = k % buf->cap;
    buf->index_ins = k;
    return 1;
}

void buffer_imprime(Buffer *buf){
    int j, i = buf->index_rem, header;
    if(buf->index_ins == buf->index_rem)
        printf("Buffer vazio\n");
    else{
        while (i != buf->index_ins) {
            if(buf->cap - buf->index_rem < 4)
                header = buf->buffer[0];
            else
                header = buf->buffer[i];
            printf("%d  -> ", header);
            i += 4;                                    // arrumar header
            for (j = 0; j < header; j++)
                printf("%c", buf->buffer[(i+j) % buf->cap]);
            printf("\n");
            i= (i + header) % buf->cap;
        }
    }
    /*for(int i = 0; i < buf->index_ins; i++){
        printf("%c %d", buf->buffer[i], i);             erro do print 13
    }
    printf("\n");*/
}

bool buffer_remove(Buffer *buf, void *p, int cap, int *tam){
    if(buf->index_ins == buf->index_rem)
        return 0;
    char* aux = (char*) p;
    int i, k;
    if(buf->cap - buf->index_rem < 4)
        buf->index_rem = 0;
    printf("%d index rem\n", buf->index_rem);
    int siz = buf->buffer[buf->index_rem];
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

int buffer_ins_verf(Buffer *buf, int tam){
    int livre = 0;
    if(buf->index_ins == buf->index_rem)
        livre = buf->cap - 4;
    else if(buf->index_ins > buf->index_rem)
        livre = (buf->cap - (buf->index_ins - buf->index_rem)) - 4;
    else if(buf->index_ins < buf->index_rem)
        livre = buf->index_rem - buf->index_ins - 4;
    if(tam > livre)
        return 1;             // nao cabe no buffer
    else
        return 0;
}

int buffer_rem_verf(Buffer *buf){
    if(buf->index_ins == buf->index_rem)
        return 1;             // ta vazio
    else
        return 0;
}

void buffer_printa(Buffer *buf){
    printf("%d %d.\n", buf->index_ins, buf->index_rem);
}
