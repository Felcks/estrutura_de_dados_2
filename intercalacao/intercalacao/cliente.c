#include "cliente.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime cliente
void imprime(Cliente *client) {
    printf("\n*********************************");
    printf("\nCliente de código ");
    printf("%d", client->cod);
    printf("\nNome: ");
    printf("%s", client->nome);
    printf("\nData de Nascimento: ");
    printf("%s", client->data_nascimento);
    printf("\n*********************************");
}

// Cria cliente. Lembrar de usar free(client)
Cliente *cliente(int cod, char *nome, char *data_nascimento) {
    Cliente *client = (Cliente *) malloc(sizeof(Cliente));
    //inicializa espaço de memória com ZEROS
    if (client) memset(client, 0, sizeof(Cliente));
    //copia valores para os campos de client
    client->cod = cod;
    strcpy(client->nome, nome);
    strcpy(client->data_nascimento, data_nascimento);
    return client;
}

// Salva cliente no arquivo out, na posicao atual do cursor
void salva(Cliente *client, FILE *out) {
    fwrite(&client->cod, sizeof(int), 1, out);
    //client->nome ao invés de &client->nome, pois string já é ponteiro
    fwrite(client->nome, sizeof(char), sizeof(client->nome), out);
    fwrite(client->data_nascimento, sizeof(char), sizeof(client->data_nascimento), out);
}

// Le um cliente do arquivo in na posicao atual do cursor
// Retorna um ponteiro para cliente lido do arquivo
Cliente *le(FILE *in) {
    Cliente *client = (Cliente *) malloc(sizeof(Cliente));
    if (0 >= fread(&client->cod, sizeof(int), 1, in)) {
	   free(client);
	   return NULL;
    }
    fread(client->nome, sizeof(char), sizeof(client->nome), in);
    fread(client->data_nascimento, sizeof(char), sizeof(client->data_nascimento), in);
    return client;
}

// Retorna tamanho do cliente em bytes
int tamanho() {
    return sizeof(int)  //cod
            + sizeof(char) * 50 //nome
            + sizeof(char) * 11; //data_nascimento
}

