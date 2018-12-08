#include"disco.h"
#include"time.h"

// 6 rota�oes por segundo = 166ms, 80ms pra trocar de trilha
#define ROTACAO 6
#define TRILHAS 80
#define SET_TRILHA 10
#define LIN_CILINDRO 2

#define TEMPO_TROCA_LINHA 80
#define TEMPO_ROTACAO 166

#define ENTRELACAMENTO 3

#define ARQUIVO "disco.mlr"
#define LEITURA 1
#define GRAVACAO 0
#define SETOR_SIZE 512


int Disk_pos[3];
FILE* fp;

void inicializa(){
  fp = fopen(ARQUIVO,"w");
  fclose(fp);
  for(int i = 0; i< 3; i++)
    Disk_pos[i] = 0;
}

void open(){
    fp = fopen(ARQUIVO,"r+");
}

void close(){
    fclose(fp);
}

void entrelacamento(int id[], int tipo, void* buff){
    int set = id[2];

    int cursor = 0;
    for(int i = 0; i < set; i++){
      cursor += ENTRELACAMENTO;
      cursor = cursor % SET_TRILHA;
    }

    printf("POS LOGICA: %d - POS REAL: %d\n",set,cursor);

    id[2] = cursor;
    disco_Acesso(id,tipo,buff);
}

void mySleep(clock_t start, long time){
    while((clock() - start)* 1000 /CLOCKS_PER_SEC < time);
}

void disco_Acesso(int id[], int tipo, void* buff){
    clock_t start = clock();
    int pos = (id[0]*SET_TRILHA) + (id[1] * TRILHAS * SET_TRILHA) + id[2];
    if(tipo == LEITURA){
        open();
        fseek (fp, pos*SETOR_SIZE, SEEK_SET);
        fread (buff, SETOR_SIZE, 1, fp);
        close();
    }
    else{
        open();
        fseek (fp, pos*SETOR_SIZE, SEEK_SET);

        fwrite (buff, SETOR_SIZE, 1, fp);
        close();
    }
    long timelapse = abs(id[1]-Disk_pos[1]) * TEMPO_TROCA_LINHA;
    int rotacao = id[2] - Disk_pos[2] < 0 ? (SET_TRILHA - abs(id[2] - Disk_pos[2])) : (id[2] - Disk_pos[2]);
    if(rotacao != 0)
      timelapse += (long)(166 / rotacao);
    printf("time : %ld\n",timelapse);
    for(int i = 0; i< 3; i++)
      Disk_pos[i] = id[i];

    mySleep(start, timelapse);
}
