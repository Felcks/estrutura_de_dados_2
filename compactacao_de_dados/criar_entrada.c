#include <stdio.h>
#include <stdlib.h>

char* nome_arquivo_entrada = "entrada.dat";

void ler_entrada(){

	FILE *arquivo_entrada;
	if ((arquivo_entrada = fopen(nome_arquivo_entrada,"rb"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de entrada\n");
        exit(1);
    }
    else{

    	int tamanhoString;
    	char string[100];
    	int tamanhoAlfabeto;
    	int simbolos_codigos[5][2];

    	fread(&tamanhoString, sizeof(int), 1, arquivo_entrada);
    	fread(string, sizeof(char), tamanhoString, arquivo_entrada);
    	fread(&tamanhoAlfabeto, sizeof(int), 1, arquivo_entrada);

    	for(int i = 0;i < tamanhoAlfabeto; i++){
    		fread(&simbolos_codigos[i][0], sizeof(int), 1, arquivo_entrada);
    		fread(&simbolos_codigos[i][1], sizeof(int), 1, arquivo_entrada);
    	}

    	printf("%i\n", tamanhoString);
		printf("%s\n", string);
		printf("%i\n", tamanhoAlfabeto);
		for(int i = 0;i < tamanhoAlfabeto; i++){
			printf("%c %i\n",simbolos_codigos[i][0], simbolos_codigos[i][1]);
		}

    	fclose(arquivo_entrada);
    }
}

int main(int argc, char** argv){

	if(argc <= 1){
		printf("Insira o nome do arquivo de entrada com .dat\n");
		return 0;
	}

	nome_arquivo_entrada = argv[1];
	FILE *arquivo_entrada;
	if ((arquivo_entrada = fopen(nome_arquivo_entrada,"w+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de entrada\n");
        exit(1);
    }
    else{

    	int tamanhoString = 21;
    	char* string = "DCCACADEACCCCCBCEBBBD";
    	int tamanhoAlfabeto = 5;
    	int simbolos_codigos[5][2] = {
    		{'A', 101},
    		{'B', 111},
    		{'C', 0},
    		{'D', 110},
    		{'E', 100}
    	};

    	fwrite(&tamanhoString, sizeof(int), 1, arquivo_entrada);
    	fwrite(string, sizeof(char), tamanhoString, arquivo_entrada);
    	fwrite(&tamanhoAlfabeto, sizeof(int), 1, arquivo_entrada);
    	for(int i = 0; i < tamanhoAlfabeto; i++){
    		fwrite(&simbolos_codigos[i][0], sizeof(int), 1, arquivo_entrada);
    		fwrite(&simbolos_codigos[i][1], sizeof(int), 1, arquivo_entrada);
    	}

    	fclose(arquivo_entrada);
    }

    ler_entrada();
}