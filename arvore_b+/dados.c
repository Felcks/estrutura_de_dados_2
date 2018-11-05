#include "dados.h"
#include "cliente.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

Dados* cria_dados(int numero_chaves, int no_pai, int d, Cliente* cliente){

	Dados *dados = (Dados*) malloc(sizeof(Dados));
	if (dados) memset(dados, 0, sizeof(Dados));
	dados->numero_chaves = numero_chaves;
	dados->no_pai = no_pai;
	dados->d = d;

	dados->registros = (Cliente*) malloc(2 * d * sizeof(Cliente));
	dados->registros[0] = *cliente;
	
    return dados;
}


void salva_dados(Dados *dados, FILE *out){

	fwrite(&dados->numero_chaves, sizeof(int), 1, out);
	fwrite(&dados->no_pai, sizeof(int), 1, out);
	fwrite(&dados->d, sizeof(int), 1, out);

	for(int i = 0; i < dados->d*2; i++){

		salva_cliente(&dados->registros[i], out);
		printf("salvando dados %i\n", dados->registros[i].cod);
	}
}

Dados* le_dados(FILE* in){

	Dados *dados = (Dados*) malloc(sizeof(Dados));
    if (0 >= fread(&dados->numero_chaves, sizeof(int), 1, in)) {
        free(dados);
        return NULL;
    }

    fread(&dados->no_pai, sizeof(int), 1, in);
    fread(&dados->d, sizeof(int), 1, in);

    dados->registros = (Cliente*) malloc(2 * dados->d * sizeof(Cliente));
    for(int i = 0; i < dados->d*2; i++){
		fread(&dados->registros[i], sizeof(Cliente), 1, in);
	}


    return dados;
}

int tamanho_dados(int d){
	 return  sizeof(int)  //cod
            + sizeof(int) //nome
            + sizeof(int); //status
            + tamanho_cliente() * d; 
}

