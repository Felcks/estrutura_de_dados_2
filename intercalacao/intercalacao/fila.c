#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

Fila *criaFila(){
	Fila *f = (Fila*)malloc(sizeof(Fila));
	f->inicio = NULL;
	f->fim = NULL;

	return f;
}


void insere(Fila *f, char *x){
	Lista *aux = (Lista*)malloc(sizeof(Lista));
	//aux->nome = (char *) malloc (10 * sizeof (char));
	strcpy(aux->nome,x);
	//aux->nome=x;
	aux->prox = NULL;
	if(f->fim != NULL){
		f->fim->prox = aux;
	}else{
		f->inicio = aux;
	}

	f->fim = aux;

}

void retira(Fila *f){
	Lista *aux = f->inicio;
	f->inicio = aux->prox;

	free(aux);
}


void libera(Fila *f){
	while(f->inicio != NULL){
		Lista *aux = f->inicio;
		//printf("Elemento: %s\n", aux->nome);
		f->inicio = aux->prox;
		free(aux);
	}

	free(f);
	printf("Fila liberada.\n");
}



// int main(){

// 	Fila *f = criaFila();
// 	char oi[2] = "oi";
// 	printf("%s\n",oi );
// 	insere(f, oi);
// 	// insere(f, 2);
// 	// insere(f, 3);
// 	// insere(f, 4);

// 	printf("%s\n",f->inicio->nome );
// 	retira(f);

// 	libera(f);

// 	return 0;
// }