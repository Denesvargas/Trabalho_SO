#include "buffer.h"

typedef struct no_add No_add;

typedef struct no_rem No_rem;

typedef struct fila_add Fila_add;

typedef struct fila_rem Fila_rem;

typedef struct {
    Buffer *buf;
    pthread_mutex_t *mutex, *f_mutex;
    Fila_add *fila;
    char *aux;
    pthread_cond_t *cond, *cond2;
    int num;
}Thread_arg_add;

typedef struct {
    Buffer *buf;
    pthread_mutex_t *mutex, *f_mutex;
    Fila_rem *fila;
    int tam, num;
    pthread_cond_t *cond, *cond2;
}Thread_arg_rem;

typedef struct {
    void *p;
    int tam;
}Ins_arg;

typedef struct {
    void *p;
    int cap;
    int *tam;
}Rem_arg;

Fila_add* fila_add_cria();

Fila_rem* fila_rem_cria();

void fila_add_ins(Fila_add *fila, void *p, int tam);

void fila_rem_ins(Fila_rem *fila, void *p, int cap, int *tam);

Ins_arg* fila_add_del(Fila_add *fila);

Rem_arg* fila_rem_del(Fila_rem *fila);

int fila_add_vazia(Fila_add *fila);

int fila_rem_vazia(Fila_rem *fila);
