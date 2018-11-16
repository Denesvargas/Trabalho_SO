#include <stdbool.h>

typedef struct buffer Buffer;

char* dataheader(int tam);

// :3
// Inicializa um buffer com capacidade para ``cap`` bytes.
// Deve ser poss�vel usar-se quantos buffers se quiser.
// Retorna um ponteiro para o buffer alocado, ou NULL se der problema.
Buffer *buffer_inicializa(int cap);

// Finaliza um buffer previamente inicializado.
// Todos os dados eventualmente em seu interior s�o perdidos.
// A mem�ria alocada na inicializa��o deve ser liberada.
// Ap�s esta chamada, o buffer n�o pode mais ser utilizado.
void buffer_finaliza(Buffer *buf);

// insere em ``buf`` o dado apontado por ``p``, contendo ``tam`` bytes.
// ``tam`` pode ser 0, mas n�o pode ser negativo.
// retorna ``false`` (e n�o altera o estado do buffer) caso n�o seja
// poss�vel.
// retorna ``true`` caso o dado tenha sido inserido no buffer.
bool buffer_insere(Buffer *buf, void *p, int tam);

// remove o pr�ximo dado de ``buf``, colocando-o na regi�o apontada por ``p``,
// que tem capacidade para ``cap`` bytes. Caso o pr�ximo dado seja maior
// que ``cap``, os dados s�o truncados, e o que n�o couber em ``p`` �
// perdido. Coloca em ``*tam`` o tamanho original do dado retirado (que pode ser
// menor, igual ou maior que ``cap``).
// ``cap`` pode ser 0. ``p`` pode ser NULL (nesse caso, ``cap`` deve ser 0).
// Retorna ``true`` se for bem sucedido, e ``false`` caso contr�rio.
bool buffer_remove(Buffer *buf, void *p, int cap, int *tam);

void buffer_imprime(Buffer *buf);

int buffer_rem_verf(Buffer *buf);
