#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int *get_bits(int n, int bitswanted){
  int *bits = malloc(sizeof(int) * bitswanted);

  int k;
  for(k=0; k<bitswanted; k++){
    int mask =  1 << k;
    int masked_n = n & mask;
    int thebit = masked_n >> k;
    bits[k] = thebit;
  }

  return bits;
}

int main(void){

	int arvore[50]; //Isso é uma árvore vetorial hihi
	//1 arquivo = 2¹

	//2 arquivos = 3 nós 2²-1 //10

	//3 arquivos = 7 nós 2³-1
	//4 arquivos = 7 nós 2³-1

	//5 arquivos = 15 nós -- 2⁴-1
	//6 = 15
	//7 = 15
	//8 = 15
	
	//9 = 31 -- 2⁵ - 1 

	int nivel = 2;
	int qtd = 9;

	for(int i = 2; i < 10; i++){
		int potencia = pow(2, i-1);

		if(potencia >= qtd){
			nivel = i;
			break;
		}
	}


	printf("%i\n", nivel);

	int arquivo_0[] = {31, 79, 999};
	int arquivo_1[] = {76, 999};
	int arquivo_2[] = {41, 999};
	int arquivo_3[] = {69, 999};
	int arquivo_4[] = {13, 40, 999};
	int arquivo_5[] = {2, 20, 51, 999};
	int arquivo_6[] = {6, 10, 15, 60, 999};

	for(int i = 0; i < 50; i++){
		arvore[i] = 999;
	}


	int n = 0; //Numero do arquivo
	int valor = 31; //Valor do primeiro carinho do arquivo
	int  bitswanted = 3; //niveis - 1
  	int *bits = get_bits(n, bitswanted);

  	// for(int i=bitswanted-1; i>=0;i--){
   //  	//printf("%d ", bits[i]);
  	// }

  	//printf("\n");

  	int pos = 1; //Lembrando que isso é ficticio na real era pra ser zero mas o calculo precsa disso
  	// vou usar pos - 1
  	for(int i=bitswanted-1; i>=-1;i--){

  		if(valor < arvore[pos-1]){
  			arvore[pos-1] = valor;
  		}

  		if(i >= 0){
	  		if(bits[i] == 0){
	  			pos = pos * 2;
	  		}
	  		else{
	  			pos = (pos * 2) + 1;
	  		}
  		}
  	}


  	//A quantidade de bits depende da quantidade de niveis
  	//4 niveis = 3 escolhas


  	n = 1; //Numero do arquivo
	valor = 76; //Valor do primeiro carinho do arquivo
	bitswanted = 3; //niveis - 1
  	bits = get_bits(n, bitswanted);
	pos = 1; //Lembrando que isso é ficticio na real era pra ser zero mas o calculo precsa disso
	  	
  	// vou usar pos - 1
  	for(int i=bitswanted-1; i>=-1;i--){

  		if(valor < arvore[pos-1]){
  			arvore[pos-1] = valor;
  		}

  		if(i >= 0){
	  		if(bits[i] == 0){
	  			pos = pos * 2;
	  		}
	  		else{
	  			pos = (pos * 2) + 1;
	  		}
  		}
  	}

  	for(int i = 0; i < 20; i++){
		printf("%i ", arvore[i]);
	}
	printf("\n");
}