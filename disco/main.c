#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"disco.h"

int main(){
    void* buff = malloc(512);
    char* pr = (char*)buff;

    void* buff2 = malloc(512);
    char* pr2 = (char*)buff2;

    int pos[] = {0,0,0};
    int pos2[] = {0,0,1};
    int pos3[] = {0,0,2};

    int pos4[] = {0,0,0};
    int pos5[] = {0,0,1};
    int pos6[] = {0,0,2};



    //strcpy(pr,"CARALHO");

  for(int j = 1; j<9; j++){

    inicializa(j);

    long tt = clock() * 1000 / CLOCKS_PER_SEC;

    long t1 = 0,t2 = 0;

    for(int i = 0; i< 10; i++){
      pos[2] = i%9;
      pos[0] = i/9;
      t1 += entrelacamento(pos,0,buff);
    }

    //printf("Fim\n");

    for(int i = 0; i< 10; i++){
      pos[2] = i%9;
      pos[0] = i/9;
      t2 += entrelacamento(pos,0,buff);
    }

    long ttt = clock() * 1000 / CLOCKS_PER_SEC;
    printf("\nENTRELACAMENTO %d\nEscrita: %ld \nLeitura: %ld \nMedia: %ld\nLeitura+Escrita: %ld \nTotal Real: %ld\n",j,t1,t2,(t1+t2)/200,t1+t2,ttt-tt);
  }

    //Testezao do krl:
/*
    strcpy(pr,"CARALHO");
    entrelacamento(pos2,0,buff);
    strcpy(pr,"CARALHO2");
    entrelacamento(pos,0,buff);
    strcpy(pr,"CARALHO3");
    entrelacamento(pos3,0,buff);

    printf("\n\nremover:\n\n");

    entrelacamento(pos4,1,buff2);
    printf("%s\n",pr2);
    entrelacamento(pos5,1,buff2);
    printf("%s\n",pr2);
    entrelacamento(pos6,1,buff2);
    printf("%s\n",pr2);
*/
}
