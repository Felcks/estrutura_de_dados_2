#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct cliente {
	int cod;
	char nome[100];
	int status;
} Cliente;

void imprime(Cliente *cliente);

Cliente *cria_cliente(int cod, char *nome);

void salva_cliente(Cliente *cliente, FILE *out);

Cliente *le_cliente(FILE *in);

int tamanho_cliente();

#endif