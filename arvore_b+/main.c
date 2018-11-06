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
	Dados* dados = cria_dados(1, -1, d, cliente);

	FILE *arquivo_dados;
	if((arquivo_dados = fopen(arquivo_dados_nome, "wb")) == NULL){
		return;
	}
	else{

		salva_dados(dados, arquivo_dados);
		arvore = cria_arvore(dados, 0);
		salvar_metadados(dados);
		fclose(arquivo_dados);

		printf("Cliente criado com código 1 e nome Matheus\n");
		printf("Arvore criada do zero!\n");
	}
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

void inserir(Cliente* cliente){

	printf("minha raiz é folha %i\n", eh_folha);
	int raiz_eh_folha = insere_arvore(arvore, cliente, eh_folha, d, arquivo_indice_nome, arquivo_dados_nome);

	//Quando a raiz deixa de ser folha - Preciso atualizar os metadados
	if(raiz_eh_folha != eh_folha){

		eh_folha = raiz_eh_folha;
		FILE *arquivo_metadados;
		if((arquivo_metadados = fopen(arquivo_metadados_nome, "wb+")) == NULL){
			return;
		}
		else{
			Metadados *metadados = cria_metadados(0, false);
			salva_metadados(metadados, arquivo_metadados);
			printf("Salvei novo metadados com raiz nao sendo folha\n");
		}
	}
}


int main(int argc, char* argv[]){

	if(argc <= 1){
		printf("Insira o 'd'\n");
		return 0;
	}

	d = atoi(argv[1]);

	ler_metadados();

	//busca_arvore(arvore, 10, eh_folha, arquivo_indice_nome, arquivo_dados_nome);


	Cliente* cliente2 = cria_cliente(10, "Felipe");
	Cliente* cliente3 = cria_cliente(11, "Felipe");
	Cliente* cliente4 = cria_cliente(12, "Felipe");
	Cliente* cliente5 = cria_cliente(13, "Felipe");


	Cliente* cliente10 = cria_cliente(7, "Felipe");
	inserir(cliente10);

	// inserir(cliente2);
	// inserir(cliente3);
	// inserir(cliente4);
	// inserir(cliente5);

	return 0;
}