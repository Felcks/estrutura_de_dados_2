#include "indice.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

Indice* cria_indice(int numero_chaves, bool aponta_para_folha, int no_pai, int d){

	Indice *indice = (Indice*) malloc(sizeof(Indice));
	if (indice) memset(indice, 0, sizeof(Indice));
	indice->numero_chaves = numero_chaves;
	indice->aponta_para_folha = aponta_para_folha;
	indice->no_pai = no_pai;

	indice->ponteiros_paginas = (int*) malloc(((2 * d) + 1) * sizeof(int));
	return indice;
}