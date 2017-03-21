#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/* le um float da linha de comando */
float getFloat();

/* recebe a string dada na linha de comando de programa e retorna o numero ligado a ela */
float extraiNumero(char *string);

/*
  mallocSafe: testa o ponteiro devolvido por malloc
 */
void * mallocSafe (size_t n);
