#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

void criaEntrada1(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(6, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
    Cliente *c2 = cliente(7, "Carlos", "01/01/1990");
    salva(c2, out);
    free(c2);
    Cliente *c3 = cliente(14, "Fátima", "02/02/1980");
    salva(c3, out);
    free(c3);
    Cliente *c4 = cliente(29, "Marcelo", "03/03/1990");
    salva(c4, out);
    free(c4);
    Cliente *c5 = cliente(46, "Silvia", "04/04/1980");
    salva(c5, out);
    free(c5);
    Cliente *c6 = cliente(48, "Ana", "01/01/1980");
    salva(c6, out);
    free(c6);
    Cliente *c7 = cliente(59, "Carlos", "01/01/1990");
    salva(c7, out);
    free(c7);
    Cliente *c8 = cliente(74, "Fátima", "02/02/1980");
    salva(c8, out);
    free(c8);
    Cliente *c9 = cliente(75, "Marcelo", "03/03/1990");
    salva(c9, out);
    free(c9);
    Cliente *c10 = cliente(76, "Silvia", "04/04/1980");
    salva(c10, out);
    free(c10);           
}

void criaEntrada2(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(4, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
    Cliente *c2 = cliente(10, "Carlos", "01/01/1990");
    salva(c2, out);
    free(c2);
    Cliente *c3 = cliente(18, "Fátima", "02/02/1980");
    salva(c3, out);
    free(c3);
    Cliente *c4 = cliente(20, "Marcelo", "03/03/1990");
    salva(c4, out);
    free(c4);
    Cliente *c5 = cliente(21, "Silvia", "04/04/1980");
    salva(c5, out);
    free(c5);
    Cliente *c6 = cliente(22, "Ana", "01/01/1980");
    salva(c6, out);
    free(c6);
    Cliente *c7 = cliente(26, "Carlos", "01/01/1990");
    salva(c7, out);
    free(c7);
    Cliente *c8 = cliente(49, "Fátima", "02/02/1980");
    salva(c8, out);
    free(c8);
    Cliente *c9 = cliente(56, "Marcelo", "03/03/1990");
    salva(c9, out);
    free(c9);
    Cliente *c10 = cliente(65, "Silvia", "04/04/1980");
    salva(c10, out);
    free(c10);           
}

void criaEntrada3(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(5, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
    Cliente *c2 = cliente(8, "Carlos", "01/01/1990");
    salva(c2, out);
    free(c2);
    Cliente *c3 = cliente(11, "Fátima", "02/02/1980");
    salva(c3, out);
    free(c3);
    Cliente *c4 = cliente(15, "Marcelo", "03/03/1990");
    salva(c4, out);
    free(c4);
    Cliente *c5 = cliente(16, "Silvia", "04/04/1980");
    salva(c5, out);
    free(c5);
    Cliente *c6 = cliente(19, "Ana", "01/01/1980");
    salva(c6, out);
    free(c6);
    Cliente *c7 = cliente(25, "Carlos", "01/01/1990");
    salva(c7, out);
    free(c7);
    Cliente *c8 = cliente(50, "Fátima", "02/02/1980");
    salva(c8, out);
    free(c8);
    Cliente *c9 = cliente(55, "Marcelo", "03/03/1990");
    salva(c9, out);
    free(c9);
    Cliente *c10 = cliente(57, "Silvia", "04/04/1980");
    salva(c10, out);
    free(c10);
    Cliente *c11 = cliente(66, "Fátima", "02/02/1980");
    salva(c11, out);
    free(c11);
    Cliente *c12 = cliente(77, "Marcelo", "03/03/1990");
    salva(c12, out);
    free(c12);
    Cliente *c13 = cliente(78, "Silvia", "04/04/1980");
    salva(c13, out);
    free(c13);                      
}

void criaEntrada4(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(9, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
    Cliente *c2 = cliente(12, "Carlos", "01/01/1990");
    salva(c2, out);
    free(c2);
    Cliente *c3 = cliente(17, "Fátima", "02/02/1980");
    salva(c3, out);
    free(c3);
    Cliente *c4 = cliente(30, "Marcelo", "03/03/1990");
    salva(c4, out);
    free(c4);
    Cliente *c5 = cliente(32, "Silvia", "04/04/1980");
    salva(c5, out);
    free(c5);
    Cliente *c6 = cliente(38, "Ana", "01/01/1980");
    salva(c6, out);
    free(c6);
    Cliente *c7 = cliente(43, "Carlos", "01/01/1990");
    salva(c7, out);
    free(c7);
    Cliente *c8 = cliente(51, "Fátima", "02/02/1980");
    salva(c8, out);
    free(c8);
    Cliente *c9 = cliente(54, "Marcelo", "03/03/1990");
    salva(c9, out);
    free(c9);
    Cliente *c10 = cliente(58, "Silvia", "04/04/1980");
    salva(c10, out);
    free(c10);
    Cliente *c11 = cliente(73, "Fátima", "02/02/1980");
    salva(c11, out);
    free(c11);
    Cliente *c12 = cliente(79, "Marcelo", "03/03/1990");
    salva(c12, out);
    free(c12);                   
}

void criaEntrada5(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(1, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
    Cliente *c2 = cliente(3, "Carlos", "01/01/1990");
    salva(c2, out);
    free(c2);
    Cliente *c3 = cliente(13, "Fátima", "02/02/1980");
    salva(c3, out);
    free(c3);
    Cliente *c4 = cliente(27, "Marcelo", "03/03/1990");
    salva(c4, out);
    free(c4);
    Cliente *c5 = cliente(31, "Silvia", "04/04/1980");
    salva(c5, out);
    free(c5);
    Cliente *c6 = cliente(36, "Ana", "01/01/1980");
    salva(c6, out);
    free(c6);
    Cliente *c7 = cliente(47, "Carlos", "01/01/1990");
    salva(c7, out);
    free(c7);
    Cliente *c8 = cliente(60, "Fátima", "02/02/1980");
    salva(c8, out);
    free(c8);
    Cliente *c9 = cliente(80, "Marcelo", "03/03/1990");
    salva(c9, out);
    free(c9);      
}
void criaEntrada6(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(99, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
}

void criaEntrada7(FILE *out) {
    printf("Criando Entrada\n");
    
    Cliente *c1 = cliente(100, "Ana", "01/01/1980");
    salva(c1, out);
    free(c1);
}
void le_cliente(FILE *in) {
    printf("\n\nLendo clientes do arquivo...\n\n");
    rewind(in);
    Cliente *f;
    while ((f = le(in)) != NULL) {
        imprime(f);
        free(f);
    }
}

int main() {
    //declara ponteiro para arquivo
    FILE *out1;
    FILE *out2;
    FILE *out3;
    FILE *out4;
    FILE *out5;
    FILE *out6;
    FILE *out7;
    
    //abre arquivo
    if ((out1 = fopen("ent0.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo1\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada1(out1);
        fclose(out1);    
    }

    if ((out2 = fopen("ent1.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo2\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada2(out2);
        fclose(out2);    
    }
    if ((out3 = fopen("ent2.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo3\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada3(out3);
        fclose(out3);    
    }
    if ((out4 = fopen("ent3.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo4\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada4(out4);
        fclose(out4);    
    }
    if ((out5 = fopen("ent4.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo1\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada5(out5);
        //le_cliente(out5);
        fclose(out5);    
    }
    if ((out6 = fopen("ent5.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo1\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada6(out6);
        //le_cliente(out5);
        fclose(out6);    
    }
if ((out7 = fopen("ent6.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo1\n");
        exit(1);
    }
    else {
        //insere cliente
        criaEntrada7(out7);
        //le_cliente(out5);
        fclose(out7);    
    }

  
  return 0;  
}

