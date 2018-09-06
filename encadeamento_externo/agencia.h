#ifndef AGENCIA_H
#define AGENCIA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct Agencia {
    int cod;
    char nome[50];
    char gerente[50];
    int prox; 
    int status;
} Agencia;


// Imprime agencia
void imprime(Agencia *agencia);

// Cria agencia. Lembrar de usar free(agencia)
Agencia *agencia(int cod, char *nome, char *gerente, int prox, int status);

// Salva agencia no arquivo out, na posicao atual do cursor
void salva(Agencia *agencia, FILE *out);

// Le uma agencia do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
Agencia *le(FILE *in);

// Retorna tamanho da agencia em bytes
int tamanho();

#endif