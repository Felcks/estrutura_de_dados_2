#include "agencia.h"
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// Imprime funcionario
void imprime(Agencia *func) {
    printf("**********************************************");
    printf("\nAgencia de código ");
    printf("%d", func->cod);
    printf("\nNome: ");
    printf("%s", func->nome);
    printf("\nGerente: ");
    printf("%s", func->gerente);
    printf("\n**********************************************");
    printf("\n");
}

// Cria funcionario. Lembrar de usar free(func)
Agencia *agencia(int cod, char *nome, char *gerente) {
    Agencia *func = (Agencia*) malloc(sizeof(Agencia));
    //inicializa espaço de memória com ZEROS
    if (func) memset(func, 0, sizeof(Agencia));
    //copia valores para os campos de func
    func->cod = cod;
    strcpy(func->nome, nome);
    strcpy(func->gerente, gerente);
    return func;
}

// Salva funcionario no arquivo out, na posicao atual do cursor
void salva(Agencia *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    //func->nome ao invés de &func->nome, pois string já é ponteiro
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->gerente, sizeof(char), sizeof(func->gerente), out);
}


// Le um funcionario do arquivo in na posicao atual do cursor
// Retorna um ponteiro para funcionario lido do arquivo
Agencia *le(FILE *in) {
    Agencia *func = (Agencia *) malloc(sizeof(Agencia));
    if (0 >= fread(&func->cod, sizeof(int), 1, in)) {
    free(func);
    return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->gerente, sizeof(char), sizeof(func->gerente), in);
    return func;
}

// Retorna tamanho do funcionario em bytes
int tamanho() {
    return  sizeof(int)  //cod
            + sizeof(char) * 50 //nome
            + sizeof(char) * 50; //gerente
}