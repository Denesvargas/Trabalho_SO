#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"disco.h"

int main(){
    void* buff = malloc(512);
    char* pr = (char*)buff;

    void* buff2 = malloc(512);
    char* pr2 = (char*)buff2;

    int pos[] = {0,0,0};
    int pos2[] = {0,0,1};
    int pos3[] = {0,0,2};

    inicializa();


    //Testezao do krl:

    strcpy(pr,"CARALHO\n");
    entrelacamento(pos2,0,buff);
    strcpy(pr,"CARALHO2\n");
    entrelacamento(pos,0,buff);
    strcpy(pr,"CARALHO3\n");
    entrelacamento(pos3,0,buff);

    printf("\n\nremover:\n\n");

    entrelacamento(pos2,1,buff2);
    printf("%s\n",pr2);
    entrelacamento(pos3,1,buff2);
    printf("%s\n",pr2);
    entrelacamento(pos,1,buff2);
    printf("%s\n",pr2);

}
