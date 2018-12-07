#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"disco.h"

int main(){
    void* buff = malloc(512);
    char* pr = (char*)buff;

    void* buff2 = malloc(512);
    char* pr2 = (char*)buff2;

    strcpy(pr,"CARALHO");

    entrelacamento(5,0,buff);

    entrelacamento(5,1,buff2);

    printf("%s\n",buff2);
}
