#include "cliente.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime agencia
void imprime(Cliente *cliente) {
    printf("**********************************************");
    printf("\nCliente de código: ");
    printf("%d", cliente->cod);
    printf("\nNome: ");
    printf("%s", cliente->nome);
    printf("\nStatus: ");
    printf("%i", cliente->status);
    printf("\n**********************************************");
    printf("\n");
}

Cliente *cria_cliente(int cod, char *nome) {
    Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    cliente->cod = cod;
    strcpy(cliente->nome, nome);
    cliente->status = 1;
    return cliente;
}

void salva_cliente(Cliente *cliente, FILE *out) {
    fwrite(&cliente->cod, sizeof(int), 1, out);
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
    fwrite(&cliente->status, sizeof(int), 1, out);
}

Cliente *le_cliente(FILE *in) {
    Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
    if (0 >= fread(&cliente->cod, sizeof(int), 1, in)) {
        free(cliente);
        return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    fread(&cliente->status, sizeof(int), 1, in);
    return cliente;
}

int tamanho_cliente() {
    return  sizeof(int)  //cod
            + sizeof(char) * 100 //nome
            + sizeof(int); //status
}