#include "dados.h"
#include "indice.h"
#include "arvore.h"
#include "metadados.h"
#include "cliente.h"
#include <stdlib.h>
#include <stdio.h>

Arvore* cria_arvore(void* elemento, int endereco){

	Arvore* arvore = malloc(sizeof(Arvore));
	arvore->ponteiro = elemento;
	arvore->endereco = endereco;
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
			arvore = cria_arvore(dados, metadados->raiz);
		}
		else{

			fseek(arquivo_indice, (tamanho_indice(d) * metadados->raiz), SEEK_SET);
			Indice *indice = le_indice(arquivo_indice);
			arvore = cria_arvore(indice, metadados->raiz);
		}
	}

	return arvore;
}

Arvore* montar_arvore_com_endereco(int endereco, int eh_folha, char* arquivo_indice_nome, char* arquivo_dados_nome, int d){

	Arvore* arvore = malloc(sizeof(Arvore));
	FILE* arquivo_dados;
	FILE* arquivo_indice;

	if((arquivo_dados = fopen(arquivo_dados_nome, "rb")) == NULL || (arquivo_indice = fopen(arquivo_indice_nome, "rb")) == NULL){

		printf("Erro ao tentar abrir arquivo de indice ou de dados\n");
		exit(0);
	}
	else{

		if(eh_folha == true){

			fseek(arquivo_dados, tamanho_dados(d) * endereco , SEEK_SET); 
			Dados *dados = le_dados(arquivo_dados);
			arvore = cria_arvore(dados, endereco);
		}
		else{

			fseek(arquivo_indice, tamanho_indice(d) * endereco, SEEK_SET);
			Indice *indice = le_indice(arquivo_indice);
			arvore = cria_arvore(indice, endereco);
		}

		fclose(arquivo_dados);
		fclose(arquivo_indice);
	}

	return arvore;
}


Cliente* busca_arvore(Arvore* arvore, int cod, int eh_folha, char* arquivo_indice_nome, char* arquivo_dados_nome){

	if(eh_folha){
		Dados* dados = (Dados*)arvore->ponteiro;
		for(int i = 0; i < dados->numero_chaves; i++){
			printf("rodando arvore %i\n", dados->registros[i].cod );
			if(dados->registros[i].cod == cod){
				printf("Achou o registro %i! \n", cod);
				return &dados->registros[i];
			}
		}
		printf("Não achou o registro %i.\n", cod);
		return NULL;
	}
	else{

		Indice* indice = (Indice*)arvore->ponteiro;
		for(int i = 0; i < indice->numero_chaves; i++){
			if(cod < indice->chaves[i]){

				Arvore* arvore_nova = montar_arvore_com_endereco(indice->ponteiros_paginas[i], indice->aponta_para_folha,
																	arquivo_indice_nome, arquivo_dados_nome, indice->d);

				return busca_arvore(arvore_nova, cod, indice->aponta_para_folha, arquivo_indice_nome, arquivo_dados_nome);
			}
		}

		//Se não achar nenhum menor vai para o último ponteiro existente
		int i = indice->numero_chaves;
		Arvore* arvore_nova = montar_arvore_com_endereco(indice->ponteiros_paginas[i], indice->aponta_para_folha,
																	arquivo_indice_nome, arquivo_dados_nome, indice->d);
		return busca_arvore(arvore_nova, cod, indice->aponta_para_folha, arquivo_indice_nome, arquivo_dados_nome);
	}
}

void insere_indice(int endereco_indice, int chave, int endereco_nova_pagina, int d, FILE* arquivo_indice, FILE* arquivo_dados){

	printf("INSERE INDICE endereco nova pagina %i\n", endereco_nova_pagina);
	fseek(arquivo_indice, tamanho_indice(d) * endereco_indice, SEEK_SET);
	Indice* indice = le_indice(arquivo_indice);

	if(indice->numero_chaves < 2*d){
		//posso adicionar mais um
		indice->chaves[indice->numero_chaves] = chave;
		indice->ponteiros_paginas[indice->numero_chaves+1] = endereco_nova_pagina;
		indice->numero_chaves += 1;
		
		for(int i = 0; i < indice->numero_chaves-1; i++){
			for(int j = (i+1); j < indice->numero_chaves; j++){

				int chaveAux, endAux;
				if(indice->chaves[i] > indice->chaves[j]){
					chaveAux = indice->chaves[i];
					endAux = indice->ponteiros_paginas[i+1];
					
					indice->chaves[i] = indice->chaves[j];
					indice->ponteiros_paginas[i+1] = indice->ponteiros_paginas[j+1];
					
					indice->chaves[j] = chaveAux;
					indice->ponteiros_paginas[j+1] = endAux;
				}
			}
		}

		fseek(arquivo_indice, tamanho_indice(d) * endereco_indice, SEEK_SET);
		salva_indice(indice, arquivo_indice);
		//Tenho que salvar indice
	}
	else{

		int chaves_array[d*2 + 1];
		for(int i = 0; i < 2*d; i++){
			chaves_array[i] = indice->chaves[i];
		}
		chaves_array[2*d] = chave;

		int ponteiros_array[d*2 + 1];
		for(int i = 0; i < 2*d; i++){
			ponteiros_array[i] = indice->ponteiros_paginas[i+1];
		}
		ponteiros_array[2*d] = endereco_nova_pagina;

		for(int i = 0; i < 2*d; i++){
			for(int j = (i+1); j < (2*d) + 1; j++){

				int chaveAux, endAux;
				if(chaves_array[i] > chaves_array[j]){
					chaveAux = chaves_array[i];
					endAux = ponteiros_array[i];
					
					chaves_array[i] = chaves_array[j];
					ponteiros_array[i] = ponteiros_array[j];
					
					chaves_array[j] = chaveAux;
					ponteiros_array[j] = endAux;
				}
			}
		}

		//Indice atual
		indice->numero_chaves = d;
		for(int i = 0; i < d; i++){
			indice->chaves[i] = chaves_array[i];
		}

		for(int i = 1; i < d+1; i++){
			indice->ponteiros_paginas[i] = ponteiros_array[i-1];
		}

		//Indice Criado
		Indice* indiceNovo = cria_indice(d+1, indice->aponta_para_folha, indice->no_pai, d);
		for(int i = 0; i < d+1; i++){
			indiceNovo->chaves[i] = chaves_array[d + i];
		}

		for(int i = 0; i < d+2; i++){
			indiceNovo->ponteiros_paginas[i] = ponteiros_array[(d-1) + i];
		}

		//Endereço novo indice
		fseek(arquivo_indice, 0, SEEK_END);
		int endereco_novo_indice = (ftell(arquivo_indice) / tamanho_indice(d)) + 1;

		//Apontar os dados para o nó indice
		if(indiceNovo->aponta_para_folha){
			for(int i = 0; i < indiceNovo->numero_chaves+1; i++){
				fseek(arquivo_dados, indiceNovo->ponteiros_paginas[i] * tamanho_dados(d), SEEK_SET);
				Dados* dados = le_dados(arquivo_dados);
				dados->no_pai = endereco_novo_indice;


				fseek(arquivo_dados, indiceNovo->ponteiros_paginas[i] * tamanho_dados(d), SEEK_SET);
				salva_dados(dados, arquivo_dados);
			}
		}
		else{
			for(int i = 0; i < indiceNovo->numero_chaves+1; i++){
				fseek(arquivo_indice, indiceNovo->ponteiros_paginas[i] * tamanho_dados(d), SEEK_SET);
				Indice* indice = le_indice(arquivo_indice);
				indice->no_pai = endereco_novo_indice;

				fseek(arquivo_indice, indiceNovo->ponteiros_paginas[i] * tamanho_dados(d), SEEK_SET);
				salva_indice(indice, arquivo_indice);
			}
		}

		if(indice->no_pai == -1){

			Indice* indice_pai = cria_indice(1, false, -1, d);
			indice_pai->chaves[0] = indiceNovo->chaves[0];
			indice_pai->ponteiros_paginas[0] = endereco_indice;
			indice_pai->ponteiros_paginas[1] = endereco_novo_indice;

			fseek(arquivo_indice, 0, SEEK_END); //Vai salvar no ultimo
			salva_indice(indice_pai, arquivo_indice);

			int endereco_pai = (ftell(arquivo_indice) / tamanho_indice(d)) - 1 ;
			indice->no_pai = endereco_pai;
			indiceNovo->no_pai = endereco_pai;

			fseek(arquivo_indice, endereco_indice * tamanho_indice(d), SEEK_SET);
			salva_indice(indice, arquivo_indice);

			fseek(arquivo_indice, 0, SEEK_END);
			salva_indice(indiceNovo, arquivo_indice);


			FILE* arquivo_metadados;
			if((arquivo_metadados = fopen("arquivo_metadados.dat", "wb+")) == NULL ){

				printf("Erro ao tentar abrir arquivo de i\n");
				exit(0);
			}
			else{

				Metadados* metadados = cria_metadados(endereco_pai, false);
				salva_metadados(metadados, arquivo_metadados);
			}

			fclose(arquivo_metadados);
			return;
		}
		else{

			fseek(arquivo_indice, endereco_indice * tamanho_indice(d), SEEK_SET);
			salva_indice(indice, arquivo_indice);

			fseek(arquivo_indice, 0, SEEK_END);
			salva_indice(indiceNovo, arquivo_indice);

			insere_indice(indice->no_pai, indiceNovo->chaves[0], endereco_novo_indice - 1, d, arquivo_indice, arquivo_dados);
		}
	}

}


int insere(Arvore* arvore, Cliente* cliente, int eh_folha, int d, FILE *arquivo_indice, FILE *arquivo_dados,
	char* arquivo_indice_nome, char* arquivo_dados_nome){

	if(eh_folha){

		if((arquivo_dados = fopen(arquivo_dados_nome, "rb+")) == NULL || (arquivo_indice = fopen(arquivo_indice_nome, "rb+")) == NULL){

			printf("Erro ao tentar abrir arquivo de indice ou de dados na hora de inserir\n");
			exit(0);
		}

		Dados* dados = (Dados*)arvore->ponteiro;
		if(dados->numero_chaves >= 2*d){

			Cliente cliente_array[d*2 + 1];
			for(int i = 0; i < 2*d; i++){
				cliente_array[i] = dados->registros[i];
			}
			cliente_array[2*d] = *cliente;


			for(int i = 0; i < (d*2); i++){
				for(int j = (i+1); j < (2*d) + 1; j++){

					Cliente aux;
					if(cliente_array[i].cod > cliente_array[j].cod){
						aux = cliente_array[i];
						cliente_array[i] = cliente_array[j];
						cliente_array[j] = aux;
					}
				}
			}

			//Página atual
			dados->numero_chaves = d;
			for(int i = 0; i < d; i++){
				dados->registros[i] = cliente_array[i];
			}

			//Página criada
			Dados* novosDados = cria_dados(d+1, -1, d, &cliente_array[d]);
			for(int i = 0; i < d+1; i++){
				novosDados->registros[i] = cliente_array[(d) + i];
			}

			
			// printf("dados antigos \n");
			// for(int i = 0; i < dados->numero_chaves; i++){
			// 	printf("%i ", dados->registros[i].cod);
			// }

			// printf("Novos dados\n");
			// for(int i = 0; i < novosDados->numero_chaves; i++){
			// 	printf("%i ", novosDados->registros[i].cod);
			// }

			//Se ele não têm pai - ESTOU NA RAIZ
			if(dados->no_pai == -1){

				//Sei disso pois vamos criar um novo indice como raiz
				dados->no_pai = 0;
				novosDados->no_pai = 0;

				fseek(arquivo_dados, 0 , SEEK_SET);
				salva_dados(dados, arquivo_dados);

				fseek(arquivo_dados, tamanho_dados(d) * 1, SEEK_SET);
				salva_dados(novosDados, arquivo_dados); 

				Indice* indice = cria_indice(1, true, -1, d);
				indice->chaves[0] = novosDados->registros[0].cod;
				indice->ponteiros_paginas[0] = 0;
				indice->ponteiros_paginas[1] = 1;

				fseek(arquivo_indice, 0, SEEK_SET);
				salva_indice(indice, arquivo_indice);

				fclose(arquivo_indice);
				fclose(arquivo_dados);

				return 0;
				//indice->ponteiros_pagina
			}
			else{

				novosDados->no_pai = dados->no_pai;

				fseek(arquivo_dados, tamanho_dados(d) * arvore->endereco, SEEK_SET);
				salva_dados(dados, arquivo_dados);

				fseek(arquivo_dados, 0, SEEK_END);
				int endereco_nova_pagina = ftell(arquivo_dados)/tamanho_dados(d);
				
				fseek(arquivo_dados, tamanho_dados(d) * endereco_nova_pagina, SEEK_SET);
				salva_dados(novosDados, arquivo_dados);

				insere_indice(novosDados->no_pai, novosDados->registros[0].cod, endereco_nova_pagina, d, arquivo_indice, arquivo_dados);

				fclose(arquivo_indice);
				fclose(arquivo_dados);
				return 0;
				//fseek(arquivo_dados, dad)
			}
			//Tenho que fazer algoritmos de inclusao como reparticao

		}
		else{

			dados->registros[dados->numero_chaves] = *cliente;
			dados->numero_chaves += 1;

			for(int i = 0; i < dados->numero_chaves-1; i++){
				for(int j = i+1; j < dados->numero_chaves; j++){

					Cliente aux;
					if(dados->registros[i].cod > dados->registros[j].cod){
						aux = dados->registros[i];
						dados->registros[i] = dados->registros[j];
						dados->registros[j] = aux;
					}
				}
			}

			fseek(arquivo_dados, tamanho_dados(d) * ((int)arvore->endereco), SEEK_SET);
			salva_dados(dados, arquivo_dados);
			printf("Insercao feita com sucesso cod %i!\n", cliente->cod);
		}

		fclose(arquivo_dados);
		fclose(arquivo_indice);
	}
	else{

		Indice* indice = (Indice*)arvore->ponteiro;

		for(int i = 0; i < indice->numero_chaves; i++){

			
			if(cliente->cod < indice->chaves[i]){
				
				Arvore* arvore_nova = montar_arvore_com_endereco(indice->ponteiros_paginas[i], indice->aponta_para_folha,
																		arquivo_indice_nome, arquivo_dados_nome, indice->d);

				insere(arvore_nova, cliente, indice->aponta_para_folha, d, arquivo_indice, arquivo_dados, arquivo_indice_nome, arquivo_dados_nome);
				return 0;
			}
		}


		int i = indice->numero_chaves;
		Arvore* arvore_nova = montar_arvore_com_endereco(indice->ponteiros_paginas[i], indice->aponta_para_folha,
																	arquivo_indice_nome, arquivo_dados_nome, indice->d);
		insere(arvore_nova, cliente, indice->aponta_para_folha, d, arquivo_indice, arquivo_dados, arquivo_indice_nome, arquivo_dados_nome);
		return 0;

	}

	return eh_folha;
}



int insere_arvore(Arvore* arvore, Cliente* cliente, int eh_folha, int d, char* arquivo_indice_nome, char* arquivo_dados_nome){

	// FILE* arquivo_dados;
	// FILE* arquivo_indice;
	// int raiz_eh_folha = eh_folha;

	// if((arquivo_dados = fopen(arquivo_dados_nome, "rb+")) == NULL || (arquivo_indice = fopen(arquivo_indice_nome, "rb+")) == NULL){

	// 	printf("Erro ao tentar abrir arquivo de indice ou de dados na hora de inserir\n");
	// 	exit(0);
	// }
	// else{
	// 	raiz_eh_folha = insere(arvore, cliente, eh_folha, d, arquivo_dados, arquivo_indice, arquivo_indice_nome, arquivo_dados_nome);
	// 	fclose(arquivo_dados);
	// 	fclose(arquivo_indice);
	// }
	
	// return raiz_eh_folha;

	FILE* arquivo_dados;
	FILE* arquivo_indice;
	int raiz_eh_folha = eh_folha;

	raiz_eh_folha = insere(arvore, cliente, eh_folha, d, arquivo_indice, arquivo_dados, arquivo_indice_nome, arquivo_dados_nome);

	return raiz_eh_folha;
}
