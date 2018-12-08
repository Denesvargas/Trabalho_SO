#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"disco.h"

int main(){
    void* buff = malloc(512);
    char* pr = (char*)buff;

    void* buff2 = malloc(512);
    char* pr2 = (char*)buff2;

    int pos[] = {1,2,8};
    int pos2[] = {1,2,8};

    inicializa();

    strcpy(pr,"CARALHO\n");

    entrelacamento(pos,0,buff);

    entrelacamento(pos2,1,buff2);

    printf("%s\n",pr2);
}
