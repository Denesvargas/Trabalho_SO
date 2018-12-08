#include"disco.h"
#include"time.h"

// 6 rota�oes por segundo = 166ms, 80ms pra trocar de trilha
#define ROTACAO 6
#define TRILHAS 80
#define SET_TRILHA 10
#define LIN_CILINDRO 2

#define TEMPO_TROCA_LINHA 80
#define TEMPO_ROTACAO 166
#define TEMPO_TROCA_SET (TEMPO_ROTACAO / SET_TRILHA)

#define ENTRELACAMENTO 3

#define ARQUIVO "disco.mlr"
#define LEITURA 1
#define GRAVACAO 0
#define SETOR_SIZE 512


int Disk_pos[3];
long passed_time;
FILE* fp;

void open(){
    fp = fopen(ARQUIVO,"r+");
}

void open_write(){
  fp = fopen(ARQUIVO,"w");
}

void close(){
    fclose(fp);
}

void inicializa(){
  open_write();
  fseek(fp, SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO, SEEK_SET);
  fputc(0, fp);
  fclose(fp);
  for(int i = 0; i< 3; i++)
    Disk_pos[i] = 0;
}

void entrelacamento(int id[], int tipo, void* buff){
    int set = id[2];

    int cursor = 0;
    for(int i = 0; i < set; i++){
      cursor += ENTRELACAMENTO;
      cursor = cursor % SET_TRILHA;
    }

    //printf("POS LOGICA: %d - POS REAL: %d\n",set,cursor);

    id[2] = cursor;
    disco_Acesso(id,tipo,buff);
}

void mySleep(clock_t start, long time){
    while((clock() - start)* 1000 /CLOCKS_PER_SEC < time);
}

void disco_Acesso(int id[], int tipo, void* buff){
    clock_t start = clock();
    int pos = (id[0]*SET_TRILHA) + (id[1] * TRILHAS * SET_TRILHA) + id[2];
    printf("posicao: %d\n",pos);
    if(tipo == LEITURA){
        open();
        fseek (fp, pos*SETOR_SIZE, SEEK_SET);
        fread (buff, SETOR_SIZE, 1, fp);
        printf("lido: %s\n", buff);
        close();
    }
    else{
        open();
        char* dk = (char*)malloc(SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO);
        fread(dk,SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO, 1,fp);
        close();
        strcpy(&dk[pos*SETOR_SIZE],buff);
        printf(" -- %s\n\n",&dk[pos*SETOR_SIZE]);
        open_write();
        fwrite (dk, SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO, 1, fp);
        close();
        free(dk);
    }

    long timelapse = abs(id[0]-Disk_pos[0]) * TEMPO_TROCA_LINHA;
    Disk_pos[2] = (Disk_pos[2] + (timelapse / TEMPO_TROCA_SET)) % SET_TRILHA;
    int rotacao = id[2] - Disk_pos[2] < 0 ? (SET_TRILHA - abs(id[2] - Disk_pos[2])) : (id[2] - Disk_pos[2]);
    if(rotacao != 0)
      timelapse += (long)(166 / rotacao);

    printf("time : %ld\n",timelapse);
    for(int i = 0; i< 3; i++)
      Disk_pos[i] = id[i];

    mySleep(start, timelapse);
}
