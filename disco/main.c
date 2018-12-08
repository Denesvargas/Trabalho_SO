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

    //Testezao do krl:

    for(int i = 0; i< 100; i++){
      pos[2] = i;
      entrelacamento(pos,0,buff);
    }

    for(int i = 0; i< 100; i++){
      pos2[0] = i;
      pos2[2] = i;
      entrelacamento(pos2,1,buff2);
    }

    //entrelacamento(pos,0,buff);

    //entrelacamento(pos2,1,buff2);

    printf("%s\n",pr2);
}
