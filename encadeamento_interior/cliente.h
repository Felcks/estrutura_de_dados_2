#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cliente {
	int cod;
	char nome[100];
	int prox;
	int status;
} Cliente;

void imprime(Cliente *cliente);

Cliente *cliente(int cod, char *nome);

void salva(Cliente *cliente, FILE *out);

Cliente *le(FILE *in);

int tamanho();

#endif