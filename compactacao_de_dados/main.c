#include <stdio.h>
#include <stdlib.h>

char* nome_arquivo_entrada = "entrada.dat";

int tamanhoString;
char string[100];
int tamanhoAlfabeto;
int simbolos_codigos[5][2];

void ler_entrada(){

	FILE *arquivo_entrada;
	if ((arquivo_entrada = fopen(nome_arquivo_entrada,"rb"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de entrada\n");
        exit(1);
    }
    else{

    	fread(&tamanhoString, sizeof(int), 1, arquivo_entrada);
    	fread(string, sizeof(char), tamanhoString, arquivo_entrada);
    	fread(&tamanhoAlfabeto, sizeof(int), 1, arquivo_entrada);

    	for(int i = 0;i < tamanhoAlfabeto; i++){
    		fread(&simbolos_codigos[i][0], sizeof(int), 1, arquivo_entrada);
    		fread(&simbolos_codigos[i][1], sizeof(int), 1, arquivo_entrada);
    	}

    	printf("ENTRADA: \n");
    	printf("%i\n", tamanhoString);
		printf("%s\n", string);
		printf("%i\n", tamanhoAlfabeto);
		for(int i = 0;i < tamanhoAlfabeto; i++){
			printf("%c %i\n",simbolos_codigos[i][0], simbolos_codigos[i][1]);
		}
		printf("\n");

    	fclose(arquivo_entrada);
    }
}

int* codifica(){

	int* saida = malloc(tamanhoString * sizeof(int));

	printf("SAÍDA\n");
	for(int i = 0; i < tamanhoString; i++){
		char c = string[i];

		for(int j = 0; j < tamanhoAlfabeto; j++){
			if(c == simbolos_codigos[j][0]){
				printf("%i", simbolos_codigos[j][1]);
				saida[i] = simbolos_codigos[j][1];
				break;
			}
		}
	}
	printf("\n\n");

	return saida;
}

void decodifica(int* texto_codificado){

	printf("DECODIFICADO \n");
	for(int i = 0; i < tamanhoString; i++){
		int codigo = texto_codificado[i];

		for(int j = 0; j < tamanhoAlfabeto; j++){
			if(codigo == simbolos_codigos[j][1]){
				printf("%c", simbolos_codigos[j][0]);
				break;
			}
		}
	}
	printf("\n");
}

int main(int argc, char* argv[]){

	if(argc <= 1){
		printf("Insira o nome do arquivo de entrada com .dat\n");
		return 0;
	}

	nome_arquivo_entrada = argv[1];
	ler_entrada();

	int* texto_codificado = codifica();
	decodifica(texto_codificado);


	return 0;
}