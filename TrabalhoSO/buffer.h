#include <stdbool.h>

typedef struct {
  int cap;
  char* buffer;
  int index;
} Buffer;

// :3
// Inicializa um buffer com capacidade para ``cap`` bytes.
// Deve ser possível usar-se quantos buffers se quiser.
// Retorna um ponteiro para o buffer alocado, ou NULL se der problema.
Buffer *buffer_inicializa(int cap);

// Finaliza um buffer previamente inicializado.
// Todos os dados eventualmente em seu interior são perdidos.
// A memória alocada na inicialização deve ser liberada.
// Após esta chamada, o buffer não pode mais ser utilizado.
void buffer_finaliza(Buffer *buf);

// insere em ``buf`` o dado apontado por ``p``, contendo ``tam`` bytes.
// ``tam`` pode ser 0, mas não pode ser negativo.
// retorna ``false`` (e não altera o estado do buffer) caso não seja
// possível.
// retorna ``true`` caso o dado tenha sido inserido no buffer.
bool buffer_insere(Buffer *buf, void *p, int tam);

// remove o próximo dado de ``buf``, colocando-o na região apontada por ``p``,
// que tem capacidade para ``cap`` bytes. Caso o próximo dado seja maior
// que ``cap``, os dados são truncados, e o que não couber em ``p`` é
// perdido. Coloca em ``*tam`` o tamanho original do dado retirado (que pode ser
// menor, igual ou maior que ``cap``).
// ``cap`` pode ser 0. ``p`` pode ser NULL (nesse caso, ``cap`` deve ser 0).
// Retorna ``true`` se for bem sucedido, e ``false`` caso contrário.
bool buffer_remove(Buffer *buf, void *p, int cap, int *tam);

void buffer_imprime(Buffer *buf);
