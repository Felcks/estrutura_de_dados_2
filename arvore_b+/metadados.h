#ifndef METADADOS_H
#define METADADOS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct metadados {
	int raiz;
	bool eh_folha;
} Metadados;

Metadados* cria_metadados(int raiz, bool eh_folha);

Metadados* le_metadados(FILE *in);

void salva_metadados(Metadados* metadados, FILE *out);


#endif
