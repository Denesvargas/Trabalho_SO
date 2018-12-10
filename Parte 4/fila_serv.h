#include "fila_thread.h"

typedef struct no_serv{
    Pacote_ped* pedido;
    struct no_serv* prox;
} No_serv;

typedef struct fila_serv{
    No_serv* no;
    int current_track;
    int direction;
} Fila_serv;

int fila_vazia(Fila_serv* fs);

No_serv* cria_no_serv(Pacote_ped* ped);

Fila_serv* cria_fila_serv();

No_serv* last_node(No_serv* no);

void fila_serv_add(Fila_serv* fs, No_serv* no);

No_serv* fila_serv_fifo(Fila_serv* fs);

No_serv* fila_serv_elev(Fila_serv* fs);
