#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"

Agencia *agencias[5];

void jogar_no_arquivo_ordenado(){

    // FILE *out;
    // //abre arquivo
    // if ((out = fopen("agencia2.dat", "w+b")) == NULL) {
    //     printf("Erro ao abrir arquivo\n");
    //     exit(1);
    // }
    // else {
    //     int i = 0;
    //     int j = 0;

    //     for( i = 0 ; i < 5; i++ ) {   
    //         for( j = 0 ; j < 5; j++ ) {   
    //           if(agencias[j]->cod == values[i]){
    //                 salva(agencias[j], out);
    //                 break;
    //             }
    //         }
    //    }

    //     fclose(out);    
    // }

    FILE *out;
    //abre arquivo
    if ((out = fopen("agencia2.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else {
         
        int j = 5;
        for( j = 0 ; j < 5; j++ ) {   
            printf("AEFAEFAEFEAF: %i \n", agencias[j]->cod);
            salva(agencias[j], out);
            // /break;
       }

        fclose(out);    
    }
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

int cmpfunc (const void * a, const void * b) {
       
       //order *orderA = (order *)a;

        Agencia** agenciaA = (Agencia *)a;
        Agencia** agenciaB = (Agencia *)b;
       // //return 1;
       // printf("compare: %i\n", (*agenciaA)->cod);
       // printf("compare2: %i\n", (*agenciaB)->cod);
       //return 1;
       return ( (*agenciaA)->cod - (*agenciaB)->cod );
}

void reordena(){
    


   // int values[5];

   // int i = 0;
   // for(i = 0; i < 5; i ++)
   //      //printf("%i\n", agencias[i]->cod);
   //      values[i] = agencias[i]->cod;

   //  qsort(values, 5, sizeof(int), cmpfunc);
   

   // printf("\nAfter sorting the list is: \n");
   // for( i = 0 ; i < 5; i++ ) {   
   //    printf("%d ", values[i]);
   // }

      int i = 0;
   for( i = 0 ; i < 5; i++ ) {   
      printf("%d ", agencias[i]->cod);
   }

    qsort(agencias, 5, sizeof(Agencia*), cmpfunc);

     printf("\n VETOR DE AGENCIAS: \n");
   for( i = 0 ; i < 5; i++ ) {   
      printf("%d ", agencias[i]->cod);
   }

    jogar_no_arquivo_ordenado();
}

void le_arquivo(){

    FILE *in;
    if ((in = fopen("agencia.dat", "r+")) == NULL) {
        printf("Erro ao abrir arquivo para leitura\n");
        exit(1);
    }
    else{
        le_agencias(in);

        fclose(in);
    }
}

void le_arquivo2(){

    FILE *in;
    if ((in = fopen("agencia2.dat", "r+")) == NULL) {
        printf("Erro ao abrir arquivo para leitura\n");
        exit(1);
    }
    else{
        printf("lendo\n");
        le_agencias(in);

        fclose(in);
    }
}

void main(int argc, char** argv) {
    //declara ponteiro para arquivo
    le_arquivo();
    reordena();
    le_arquivo2();

    FILE *out;
    //abre arquivo
    // if ((out = fopen("agencia.dat", "w+b")) == NULL) {
    //     printf("Erro ao abrir arquivo\n");
    //     exit(1);
    // }
    // else {

    //     Agencia* agencia1 = agencia(1, "ITAU", "MARCELO");
    //     Agencia* agencia2 = agencia(2, "BRADESCO", "MARCELO");
    //     Agencia* agencia3 = agencia(3, "SANTANDER", "MARCELO");
    //     Agencia* agencia4 = agencia(4, "PARMALAT", "MARCELO");
    //     Agencia* agencia5 = agencia(5, "NESTLE", "MARCELO");
        

    //     salva(agencia2, out);
    //     salva(agencia1, out);
    //     salva(agencia5, out);
    //     salva(agencia4, out);
    //     salva(agencia3, out);
        



    //     // //insere funcionários
    //     // insere_5_funcionarios(out);
    //     // //volta ao início do arquivo e lê os funcionários inseridos
    //     // le_funcionarios(out);
    //     // //volta ao início do arquivo e lê o segundo funcionário
    //     // le_segundo_funcionario(out);
    //     // //grava mais um funcionário no final do arquivo
    //     // adiciona_funcionario(out);
    //     // //sobrescreve quarto funcionário
    //     // sobrescreve_quarto_funcionario(out);
    //     // //lendo o arquivo todo novamente
    //     // le_funcionarios(out);
        
    //     // //fecha arquivo
    //     fclose(out);    
    // }


   
}