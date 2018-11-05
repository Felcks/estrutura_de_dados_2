#ifndef DADOS_H
#define DADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct indice{
	int numero_chaves;
	bool aponta_para_folha;
	int no_pai;
	int* ponteiros_paginas;
} Indice;

Indice* cria_indice(int numero_chaves, bool aponta_para_folha, int no_pai, int d);


#endif