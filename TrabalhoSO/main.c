#include <stdio.h>
#include <string.h>
#include "buffer.h"
int main(){
    Buffer* buf = buffer_inicializa(10000);
    char* teste1 = "aaaaaaa", teste2 = "bb";
    printf(">%d<", strlen(teste1));
    buffer_insere(buf, teste1, strlen(teste1));
}
