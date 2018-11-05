#include "metadados.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>


Metadados* cria_metadados(int raiz, bool eh_folha){
	
	Metadados* metadados = (Metadados*)malloc(sizeof(Metadados));
	if (metadados) memset(metadados, 0, sizeof(Metadados));
	metadados->raiz = raiz;
	metadados->eh_folha = eh_folha;
	return metadados;	
}


Metadados* le_metadados(FILE *in){

	Metadados* metadados = (Metadados*)malloc(sizeof(Metadados));
	if (0 >= fread(&metadados->raiz, sizeof(int), 1, in)) {
        free(metadados);
        return NULL;
    }
    fread(&metadados->eh_folha, sizeof(bool), 1, in);
    return metadados;
}

void salva_metadados(Metadados* metadados, FILE *out){

	fwrite(&metadados->raiz, sizeof(int), 1, out);
	fwrite(&metadados->eh_folha, sizeof(bool), 1, out);
}

