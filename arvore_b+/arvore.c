#include "dados.h"
#include "arvore.h"
#include "metadados.h"
#include "indice.h"
#include "cliente.h"
#include <stdlib.h>
#include <stdio.h>

Arvore* cria_arvore(void* elemento){

	Arvore* arvore = malloc(sizeof(Arvore));
	arvore->ponteiro = elemento;
	return arvore;
}

Arvore* montar_arvore(Metadados* metadados, char* arquivo_indice_nome, char* arquivo_dados_nome, int d){

	Arvore* arvore = malloc(sizeof(Arvore));
	FILE* arquivo_dados;
	FILE* arquivo_indice;

	if((arquivo_dados = fopen(arquivo_dados_nome, "rb")) == NULL || (arquivo_indice = fopen(arquivo_indice_nome, "rb")) == NULL){

		printf("Erro ao tentar abrir arquivo de indice ou de dados\n");
		exit(0);
	}
	else{

		if(metadados->eh_folha == true){

			fseek(arquivo_dados, tamanho_dados(d) * metadados->raiz , SEEK_SET); 
			Dados *dados = le_dados(arquivo_dados);
			arvore = cria_arvore(dados);
		}
		else{
			//Aqui tem um miniparto
		}
	}

	return arvore;
}


Cliente* busca_arvore(Arvore* arvore, int cod, int eh_folha){

	if(eh_folha){
		Dados* dados = (Dados*)arvore->ponteiro;
		for(int i = 0; i < dados->numero_chaves; i++){
			if(dados->registros[i].cod == cod){
				printf("Achou o registro %i! \n", cod);
				return &dados->registros[i];
			}
		}
		printf("Não achou o registro.\n");
		return NULL;
	}
}


void insere(Arvore* arvore, Cliente* cliente, int eh_folha, int d, FILE *arquivo_dados, FILE *arquivo_indice){

	if(eh_folha){

		Dados* dados = (Dados*)arvore->ponteiro;
		if(dados->numero_chaves >= 2*d){

			Cliente cliente_array[d*2 + 1];
			for(int i = 0; i < 2*d; i++){

				cliente_array[i] = dados->registros[i];
			}


			// Cliente* aux;
			// for(int i = 0; i < (d*2)+1; i++){
			// 	if(cliente->cod < cliente_array[i].cod){
			// 		aux = &cliente_array[i];
			// 		printf("cli %i\n", aux[i].cod);
			// 		cliente_array[i] = *cliente;
			// 		cliente = aux;
			// 		printf("aux %i\n", aux->cod);
			// 	}
			// 	else{
			// 		if(cliente_array[i].status == 0){
			// 			cliente_array[i] = *cliente;
			// 			break;
			// 		}
			// 	}
			// }
			

			printf("aqui \n");
			for(int i = 0; i < 2*d + 1; i++){
				printf("%i ", cliente_array[i].cod);
			}
			//Tenho que fazer algoritmos de inclusao como reparticao

		}
		else{

			Cliente* aux;
			for(int i = 0; i < d*2; i++){

				if(cliente->cod < dados->registros[i].cod){
					aux = &dados->registros[i];
					dados->registros[i] = *cliente;
					cliente = aux;
				}
				else{
					printf("%i \n", dados->registros[i].status);
					if(dados->registros[i].status == 0){
						dados->registros[i] = *cliente;
						dados->numero_chaves += 1;
						break;
					}
				}
			}

			//printf("aa %i\n", tamanho_dados(d) * ((int)arvore->endereco));
			fseek(arquivo_dados, tamanho_dados(d) * ((int)arvore->endereco), SEEK_SET);
			salva_dados(dados, arquivo_dados);
			printf("Insercao feita com sucesso!\n");
		}
	}
	else{

	}
}



void insere_arvore(Arvore* arvore, Cliente* cliente, int eh_folha, int d, char* arquivo_indice_nome, char* arquivo_dados_nome){

	FILE* arquivo_dados;
	FILE* arquivo_indice;

	if((arquivo_dados = fopen(arquivo_dados_nome, "rb+")) == NULL || (arquivo_indice = fopen(arquivo_indice_nome, "rb+")) == NULL){

		printf("Erro ao tentar abrir arquivo de indice ou de dados na hora de inserir\n");
		exit(0);
	}
	else{
		insere(arvore, cliente, eh_folha, d, arquivo_dados, arquivo_indice);
		fclose(arquivo_dados);
		fclose(arquivo_indice);
	}
	
}
