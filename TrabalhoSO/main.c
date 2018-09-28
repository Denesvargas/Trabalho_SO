#include <stdio.h>
#include <string.h>
#include "buffer.h"

int main(){
    Buffer* buf = buffer_inicializa(10000);
    char* teste1 = "abcdef", *teste2 = "bbbbbbbb";
    buffer_insere(buf, teste1, strlen(teste1));
    printf("cuzaomain\n");
    buffer_insere(buf, teste2, strlen(teste2));
    buffer_imprime(buf);
}
