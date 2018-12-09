#include"disco.h"
#include"time.h"


// 6 rota�oes por segundo = 166ms, 80ms pra trocar de trilha
#define ROTACAO 6
#define TRILHAS 40
#define SET_TRILHA 9
#define LIN_CILINDRO 2

#define TEMPO_TRANSF 22
#define TEMPO_TROCA_LINHA 6
#define TEMPO_ROTACAO 200
#define TEMPO_TROCA_SET (TEMPO_ROTACAO / SET_TRILHA)

#define ENTRELACAMENTO 1

#define ARQUIVO "disco.mlr"
#define LEITURA 1
#define GRAVACAO 0
#define SETOR_SIZE 512


int Disk_pos[3];
long passed_time;
int Ent_Setor[SET_TRILHA];
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

int isIn(int val){
  for(int i = 0; i< SET_TRILHA; i++){
    if(Ent_Setor[i] == val)
      return 1;
  }
  return 0;
}

void calcula_set(int ent){
  int cursor = 0;
  for(int i = 0; i< SET_TRILHA; i++)
    Ent_Setor[i] = -1;

  for(int i = 0; i < SET_TRILHA; i++){
    while(isIn(cursor))
      cursor++;
    Ent_Setor[i] = cursor;
    cursor += ent;
    cursor = cursor % SET_TRILHA;
  }

  for(int i = 0; i< SET_TRILHA; i++){
    //printf(" %d : %d\n",i,Ent_Setor[i]);
  }
}

void inicializa(int ent){
  open_write();
  fseek(fp, SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO, SEEK_SET);
  fputc(0, fp);
  fclose(fp);
  for(int i = 0; i< 3; i++)
    Disk_pos[i] = 0;
  long t1 = time(NULL);
  while(time(NULL) - t1 < 1);
  passed_time = (clock() * 1000) / CLOCKS_PER_SEC;
  calcula_set(ent);
}

long entrelacamento(int id[], int tipo, void* buff){


    //printf("POS LOGICA: %d - POS REAL: %d\n",id[2],Ent_Setor[id[2]]);

    id[2] = Ent_Setor[id[2]];
    return disco_Acesso(id,tipo,buff);
}

void mySleep(clock_t start, long time){
    while((clock() - start)* 1000 /CLOCKS_PER_SEC < time);
}

long disco_Acesso(int id[], int tipo, void* buff){
    clock_t start = clock();
    int pos = (id[0]*SET_TRILHA) + (id[1] * TRILHAS * SET_TRILHA) + id[2];
    //printf("posicao: %d\n",pos);
    if(tipo == LEITURA){
        open();
        fseek (fp, pos*SETOR_SIZE, SEEK_SET);
        fread (buff, SETOR_SIZE, 1, fp);
        //printf("lido: %s\n", buff);
        close();
    }
    else{
        open();
        char* dk = (char*)malloc(SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO);
        fread(dk,SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO, 1,fp);
        close();
        strcpy(&dk[pos*SETOR_SIZE],buff);
        //printf(" -- %s\n\n",&dk[pos*SETOR_SIZE]);
        open_write();
        fwrite (dk, SETOR_SIZE * TRILHAS * SET_TRILHA * LIN_CILINDRO, 1, fp);
        close();
        free(dk);
    }
    long timelapse = abs(id[0]-Disk_pos[0]) * TEMPO_TROCA_LINHA;
    Disk_pos[2] = ((clock()-passed_time) / TEMPO_TROCA_SET) % SET_TRILHA;
    printf("-- pa: %d  --  pf: %d --\n",Disk_pos[2],id[2]);
    int rotacao = id[2] - Disk_pos[2] < 0 ? (SET_TRILHA - abs(id[2] - Disk_pos[2])) : (id[2] - Disk_pos[2]);
    //printf("id: %d   Disk: %d ",id[2],Disk_pos[2]);
    timelapse += (TEMPO_TROCA_SET * rotacao);
    timelapse += TEMPO_TRANSF;
    //printf("time : %ld\n",timelapse);

    Disk_pos[0] = id[0];

    mySleep(start, timelapse);
    return timelapse;
}
