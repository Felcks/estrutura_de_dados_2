#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"

Agencia *agencias[5];

char* arquivo_agencia = "arquivo_agencia.dat";
char* arquivo_agencia_ordenado = "arquivo_agencia_ordenado.dat";

void insere_ordenado(char* arquivo){

    FILE *out;

    //abre arquivo
    if ((out = fopen(arquivo, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
         
        int j = 0;
        for( j = 0 ; j < 5; j++ ) {
            salva(agencias[j], out);
        }

        fclose(out);    
    }
}


int cmpfunc (const void * a, const void * b) {
       
    Agencia** agenciaA = (Agencia *)a;
    Agencia** agenciaB = (Agencia *)b;

    return ( (*agenciaA)->cod - (*agenciaB)->cod );
}

void reordena(char* arquivo){

    qsort(agencias, 5, sizeof(Agencia*), cmpfunc);
    insere_ordenado(arquivo);
}


void le_agencias(FILE *in) {

    printf("\n\nLendo agencias do arquivo...\n\n");
    rewind(in);
    Agencia *f;

    int i = 0;
    while ((f = le(in)) != NULL) {
        agencias[i] = f;
        i++;

        imprime(f);
        //free(f);
    }
}

void le_arquivo(char* arquivo){

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

/* Isere 5 agências desordenadamente */
void insere_5_agencias(){

    FILE *out;

    //abre arquivo
    if ((out = fopen(arquivo_agencia, "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {

        Agencia* agencia1 = agencia(1, "ITAU", "MARCELO");
        Agencia* agencia2 = agencia(2, "BRADESCO", "MARCELO");
        Agencia* agencia3 = agencia(3, "SANTANDER", "MARCELO");
        Agencia* agencia4 = agencia(4, "PARMALAT", "MARCELO");
        Agencia* agencia5 = agencia(5, "NESTLE", "MARCELO");
        

        salva(agencia2, out);
        salva(agencia1, out);
        salva(agencia5, out);
        salva(agencia4, out);
        salva(agencia3, out);
        
        //fecha arquivo
        fclose(out);    
    }
}


void main(int argc, char** argv) {

    
    //Inserindo 5 Agências desordenadamente
    insere_5_agencias();

    //Lendo arquivo desordenado
    le_arquivo(arquivo_agencia);

    //Reordenando e jogando no arquivo
    reordena(arquivo_agencia_ordenado);

    //Lendo arquivo ordenado
    le_arquivo(arquivo_agencia_ordenado);   
}