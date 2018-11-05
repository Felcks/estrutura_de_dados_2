#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cliente.h"

typedef struct dados{
	int numero_chaves;
	int no_pai;
	int d;
	int proxima_pagina;
	Cliente* registros;
} Dados;

Dados* cria_dados(int numero_chaves, int no_pai, int d, Cliente* cliente);

void salva_dados(Dados *dados, FILE *out);

Dados* le_dados(FILE* in);

int tamanho_dados(int d);


#endif