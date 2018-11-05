#include "metadados.h"
#include "cliente.h"
#include "dados.h"
#include "indice.h"
#include "arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

char* arquivo_metadados_nome = "arquivo_metadados.dat";
char* arquivo_indice_nome = "arquivo_indice.dat";
char* arquivo_dados_nome = "arquivo_dados.dat";

int d;
int eh_folha;
Arvore* arvore;

void salvar_metadados(Dados* dados);

void criar_raiz(){

	Cliente* cliente = cria_cliente(1, "Matheus");
	Dados* dados = cria_dados(1, 0, d, cliente);

	FILE *arquivo_dados;
	if((arquivo_dados = fopen(arquivo_dados_nome, "wb")) == NULL){
		return;
	}
	else{

		salva_dados(dados, arquivo_dados);
		arvore = cria_arvore(dados);
		salvar_metadados(dados);
		fclose(arquivo_dados);

		printf("Cliente criado com código 1 e nome Matheus\n");
		printf("Arvore criada do zero!\n");
	}


	//Indice* indice = cria_indice(1, false, 0, d);
}

void salvar_metadados(Dados* dados){

	FILE *arquivo_metadados;
	if((arquivo_metadados = fopen(arquivo_metadados_nome, "wb")) == NULL){
		return;
	}
	else{
		Metadados *metadados = cria_metadados(0, true);
		eh_folha = true;
		salva_metadados(metadados, arquivo_metadados);
		fclose(arquivo_metadados);
	}
}

void ler_metadados(){

	FILE *arquivo_metadados;
	if((arquivo_metadados = fopen(arquivo_metadados_nome, "rb")) == NULL){
		printf("Não foi possivel abrir o arquivo metadados\n");
		criar_raiz();
		//return;
	}
	else{

		Metadados* metadados = le_metadados(arquivo_metadados);
		eh_folha = metadados->eh_folha;
		fclose(arquivo_metadados);

		arvore = montar_arvore(metadados, arquivo_indice_nome, arquivo_dados_nome, d);
		printf("Arvore Montada!\n");
	}

}


int main(int argc, char* argv[]){

	if(argc <= 1){
		printf("Insira o 'd'\n");
		return 0;
	}

	d = atoi(argv[1]);

	ler_metadados();

	busca_arvore(arvore, 1, eh_folha);



	Cliente* cliente = cria_cliente(0, "Felipe");
	insere_arvore(arvore, cliente, eh_folha, d, arquivo_indice_nome, arquivo_dados_nome);

	return 0;
}