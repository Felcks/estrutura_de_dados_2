#ifndef FILA_H
#define FILA_H

#include <stdlib.h>
#include <stdio.h>

struct lista{
	char nome[10];
	FILE *input;
	struct lista *prox;
};
typedef struct lista Lista;

struct fila{
	Lista *inicio;
	Lista *fim;
};

typedef struct fila Fila;

Fila *criaFila();

void insere(Fila *f, char *x);

void retira(Fila *f);

void libera(Fila *f);

#endif