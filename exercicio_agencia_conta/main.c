#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"

char* arquivo_agencia = "arquivo_agencia.dat";
char* arquivo_conta = "arquivo_conta.dat";

Agencia *agencias[5];

void le_agencias(FILE *in) {

    printf("\n\nLendo agencias do arquivo...\n\n");
    rewind(in);
    Agencia* f;

    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

void le_arquivo_agencia(char* arquivo){

    FILE *in;
    if ((in = fopen(arquivo, "r+")) == NULL) {
        printf("Erro ao abrir arquivo para leitura\n");
        exit(1);
    }
    else{
        le_agencias(in);

        fclose(in);
    }
}

void insere_agencia(){

    FILE *out;

    //abre arquivo
    if ((out = fopen(arquivo_agencia, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {

        Agencia* agencia1 = agencia(1, "ITAU", "MARCELO");
    
        salva(agencia1, out);

        fclose(out);
    }
}

void main(int argc, char** argv) {

    insere_agencia();

    le_arquivo_agencia(arquivo_agencia);



    //ler agencias
    //inserrir agencias
    //sair do programa
}