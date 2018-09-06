#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"

char* arquivo_agencia = "agencias.dat";
char* arquivo_hash = "compartilhamento_hash.dat";

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

        Agencia* agencia1 = agencia(1, "ITAU", "MARCELO", -1, 1);
        Agencia* agencia2 = agencia(2, "BRADESCO", "MARCELO", -1, 1);
        Agencia* agencia3 = agencia(3, "BANCO DO BRASIL", "MARCELO", -1, 1);
        Agencia* agencia4 = agencia(4, "SATANDER", "MARCELO", -1, 1);
        Agencia* agencia5 = agencia(5, "CAIXA ECONOMICA", "MARCELO", -1, 1);
    
        salva(agencia1, out);
        salva(agencia2, out);
        salva(agencia3, out);
        salva(agencia4, out);
        salva(agencia5, out);

        fclose(out);
    }
}

void insere_menos_1(){

    FILE *out;
    if ((out = fopen(arquivo_hash,"wb+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo\n");
        exit(1);
    }
    else{
        int vEntrada[7] = {-1, -1, -1, -1, -1, -1, -1};
        for (int i = 0; i < 7; i++)
        {
            fwrite(&vEntrada[i], sizeof(int), 1, out);
        }
        fflush(out);
    }

   printf("Escrevendo as entradas no arquivo (entrada.dat):\n");
    rewind(out);
    int i = 0;
    while (fread(&i, sizeof(int), 1, out) != 0) {
        
        printf("%i ",i);
    }
    printf("\n");

    fclose(out);
}

void main(int argc, char** argv) {

    insere_menos_1();

    insere_agencia();

    le_arquivo_agencia(arquivo_agencia);



    //ler agencias
    //inserrir agencias
    //sair do programa
}