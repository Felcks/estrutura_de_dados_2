#ifndef ARVORE_H
#define ARVORE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "metadados.h"
#include "indice.h"
#include "dados.h"
#include "cliente.h"

typedef struct arvore{
	void* ponteiro;
	int endereco;
} Arvore;

Arvore* cria_arvore(void* elemento);

void printa_arvore(Arvore* arvore);

Arvore* montar_arvore(Metadados* metadados, char* arquivo_indice_nome, char* arquivo_dados_nome, int d);

Cliente* busca_arvore(Arvore* arvore, int cod, int eh_folha);

void insere_arvore(Arvore* arvore, Cliente* cliente, int eh_folha, int d, char* arquivo_indice_nome, char* arquivo_dados_nome);

#endif