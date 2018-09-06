#include "agencia.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime agencia
void imprime(Agencia *agencia) {
    printf("**********************************************");
    printf("\nAgencia de código ");
    printf("%d", agencia->cod);
    printf("\nNome: ");
    printf("%s", agencia->nome);
    printf("\nGerente: ");
    printf("%s", agencia->gerente);
    printf("\nProximo: ");
    printf("%i", agencia->prox);
     printf("\nStatus: ");
    printf("%i", agencia->status);
    printf("\n**********************************************");
    printf("\n");
}

// Cria agencia. Lembrar de usar free(agencia)
Agencia *agencia(int cod, char *nome, char *gerente, int prox, int status) {
    Agencia *agencia = (Agencia*) malloc(sizeof(Agencia));
    //inicializa espaço de memória com ZEROS
    if (agencia) memset(agencia, 0, sizeof(Agencia));
    //copia valores para os campos de agencia
    agencia->cod = cod;
    strcpy(agencia->nome, nome);
    strcpy(agencia->gerente, gerente);
    agencia->prox = prox;
    agencia->status = status;
    return agencia;
}

// Salva agencia no arquivo out, na posicao atual do cursor
void salva(Agencia *agencia, FILE *out) {
    fwrite(&agencia->cod, sizeof(int), 1, out);
    //agencia->nome ao invés de &agencia->nome, pois string já é ponteiro
    fwrite(agencia->nome, sizeof(char), sizeof(agencia->nome), out);
    fwrite(agencia->gerente, sizeof(char), sizeof(agencia->gerente), out);
    fwrite(&agencia->prox, sizeof(int), 1, out);
    fwrite(&agencia->status, sizeof(int), 1, out);
}


// Le um agencia do arquivo in na posicao atual do cursor
// Retorna um ponteiro para agencia lido do arquivo
Agencia *le(FILE *in) {
    Agencia *agencia = (Agencia *) malloc(sizeof(Agencia));
    if (0 >= fread(&agencia->cod, sizeof(int), 1, in)) {
    free(agencia);
    return NULL;
    }
    fread(agencia->nome, sizeof(char), sizeof(agencia->nome), in);
    fread(agencia->gerente, sizeof(char), sizeof(agencia->gerente), in);
    fread(&agencia->prox, sizeof(int), 1, in);
    fread(&agencia->status, sizeof(int), 1, in);
    return agencia;
}

// Retorna tamanho do agencia em bytes
int tamanho() {
    return  sizeof(int)  //cod
            + sizeof(char) * 50 //nome
            + sizeof(char) * 50 //gerente
            + sizeof(int) //prox
            + sizeof(int); //status
}