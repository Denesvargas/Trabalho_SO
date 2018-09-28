#include <stdio.h>
#include "buffer.h"
int main(){
    Buffer* buf = buffer_inicializa(10000);
    char* teste1 = "aaaaaa", teste2 = "bb";
    printf(">%d<", sizeof(teste1));
    buffer_insere(buf, teste1, sizeof(teste1));
}
