#include"disco.h"


#define ROTACAO 6
#define TRILHAS 80
#define SET_TRILHA 15
#define LIN_CILINDRO 2
#define TROCA_LINHA 80

#define ENTRELACAMENTO 2

#define ARQUIVO "disco.mlr"
#define LEITURA 1
#define GRAVACAO 0
#define SETOR_SIZE 512

FILE* fp;

void open(){
    fp = fopen(ARQUIVO,"r+");
}

void close(){
    fclose(fp);
}

void entrelacamento(int id, int tipo, void* buff){
    int setores = LIN_CILINDRO * SET_TRILHA * TRILHAS;

    int fator = setores/ENTRELACAMENTO;
    int novoID = id/fator + ((id - (fator * (id/fator) ))*ENTRELACAMENTO);

    printf("POS LOGICA: %d - POS REAL: %d\n",id,novoID);

    disco_Acesso(novoID,tipo,buff);
}

void disco_Acesso(int id, int tipo, void* buff){
    if(tipo == LEITURA){
        open();
        fseek (fp, id*SETOR_SIZE, SEEK_SET);

        fread (buff, SETOR_SIZE, 1, fp);
        close();
    }
    else{

        open();
        fseek (fp, id*SETOR_SIZE, SEEK_SET);

        fwrite (buff, SETOR_SIZE, 1, fp);
        close();
    }
}
