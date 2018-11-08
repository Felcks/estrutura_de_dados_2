#ifndef INDICE_H
#define INDICE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct indice{
	int numero_chaves;
	bool aponta_para_folha;
	int no_pai;
	int d;
	int* ponteiros_paginas;
	int* chaves;
} Indice;

Indice* cria_indice(int numero_chaves, bool aponta_para_folha, int no_pai, int d);

void salva_indice(Indice* indice, FILE* out);

Indice* le_indice(FILE* in);

int tamanho_indice(int d);

void imprime_indice(Indice *indice, int endereco);

#endif