#include "buffer.h"

typedef struct no_add No_add;

typedef struct fila_add Fila_add;

typedef struct {
    void *p;
    int tam;
}Ins_arg;

Fila_add* fila_add_cria();

void fila_add_ins(Fila_add *fila, void *p, int tam);

Ins_arg* fila_add_del(Fila_add *fila);

int fila_add_vazia(Fila_add *fila);

typedef struct no_rem No_rem;

typedef struct fila_rem Fila_rem;

typedef struct {
    void *p;
    int cap;
    int *tam;
}Rem_arg;

struct no_rem{
    Rem_arg *call;
    No_rem* prox;
};

struct fila_rem{
    No_rem* ini;
};

Fila_rem* fila_rem_cria();

void fila_rem_ins(Fila_rem *fila, void *p, int cap, int *tam);

Rem_arg* fila_rem_del(Fila_rem *fila);

int fila_rem_vazia(Fila_rem *fila);

typedef struct {
    Buffer *buf_serv;
    Buffer **buf_clie;
}Thread_arg_serv;

typedef struct {
    Buffer *buf_serv, *buf;
    int num;
}Thread_arg_clie;

typedef struct {
    int *id_setor, op, id_buf;
    char *buff;
}Pacote_ped;

typedef struct {
    int resp;
    char *buff;
}Pacote_resp;







