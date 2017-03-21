#include "StringOps.h"

/* le um float da linha de comando */
float getFloat()
{
    float p = -1;
    scanf("%f", &p);
    return p;
}

/* recebe a string dada na linha de comando de programa e retorna o numero ligado a ela */
float extraiNumero(char *string)
{
    int i;
    int tamanhoString = strlen(string);
    char numero[tamanhoString - 1];
    for(i = 2; i < tamanhoString; i++)
    {
        numero[i - 2] = string[i];
    }
    numero[tamanhoString - 2] = '\0';
    return atof(numero);
}

/*
  mallocSafe: testa o ponteiro devolvido por malloc
 */
void * mallocSafe (size_t n)
{
  void * pt;
  pt = malloc(n);
  if (pt == NULL) {
    printf("ERRO na alocacao de memoria.\n\n");
    exit(-1);
  }
  return pt;
}

