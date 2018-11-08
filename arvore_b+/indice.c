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
	indice->d = d;

	indice->ponteiros_paginas = (int*) malloc(((2 * d) + 1) * sizeof(int));
	indice->chaves = (int*) malloc(((2 * d)) * sizeof(int));
	return indice;
}


void salva_indice(Indice* indice, FILE* out){

	fwrite(&indice->numero_chaves, sizeof(int), 1, out);
	fwrite(&indice->aponta_para_folha, sizeof(bool), 1, out);
	fwrite(&indice->no_pai, sizeof(int), 1, out);
	fwrite(&indice->d, sizeof(int), 1, out);

	for(int i = 0; i < (indice->d*2) + 1; i++){

		fwrite(&indice->ponteiros_paginas[i], sizeof(int), 1, out);
		//printf("salvando ponteiros_paginas %i\n", indice->ponteiros_paginas[i]);
	}

	for(int i = 0; i < (indice->d*2); i++){

		fwrite(&indice->chaves[i], sizeof(int), 1, out);
		//printf("salvando chaves %i\n", indice->chaves[i]);
	}
}


Indice* le_indice(FILE* in){

	Indice *indice = (Indice*) malloc(sizeof(Indice));
    if (0 >= fread(&indice->numero_chaves, sizeof(int), 1, in)) {
        free(indice);
        return NULL;
    }

    fread(&indice->aponta_para_folha, sizeof(bool), 1, in);
    fread(&indice->no_pai, sizeof(int), 1, in);
    fread(&indice->d, sizeof(int), 1, in);


    indice->ponteiros_paginas = (int*) malloc(((2 * indice->d) + 1) * sizeof(int));
    for(int i = 0; i < (indice->d*2) + 1; i++){

		fread(&indice->ponteiros_paginas[i], sizeof(int), 1, in);
	}

	indice->chaves = (int*) malloc((2*indice->d) * sizeof(int));
	for(int i = 0; i < (indice->d*2); i++){

		fread(&indice->chaves[i], sizeof(int), 1, in);
	}

    return indice;

}

int tamanho_indice(int d){
	return  sizeof(int)  //num chaves
            + sizeof(bool) //aponta para folha
            + sizeof(int) //no pai
            + sizeof(int) //d
            + sizeof(int) * ((d*2) + 1) //ponteiro paginas
            + sizeof(int) * (d*2); //Chaves
}


void imprime_indice(Indice *indice, int endereco){
	printf("**********************************************");
    printf("\nIndice endereco: ");
    printf("%d", endereco);
    printf("\nIndice aponta para folha: ");
    printf("%i", indice->aponta_para_folha);
    printf("\nIndice no pai: ");
    printf("%i", indice->no_pai);
    printf("\nIndice chaves: ");
    for(int j = 0; j < indice->numero_chaves; j++){
		printf("%i ", indice->chaves[j]);
	}

	printf("\nIndice ponteiros: ");
	printf("%i ", indice->ponteiros_paginas[0]);
	for(int j = 0; j < indice->numero_chaves; j++){
		printf("%i ", indice->ponteiros_paginas[j+1]);
	}
    printf("\n**********************************************");
    printf("\n");
}