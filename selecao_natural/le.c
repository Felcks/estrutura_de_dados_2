#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	FILE *input;
	printf("_part0_\n");
	if ((input = fopen("part0.dat","rb"))==NULL)
	{
		printf("Nao foi possivel abir o arquivo\n");
		exit(1);
	}
	rewind(input);
	int aux;
	fread(&aux, sizeof(int), 1, input); 
	while(feof(input)==0){			
		printf("%d ",aux);
		fread(&aux, sizeof(int), 1, input);
	}

	fclose(input);

	printf("\n\n");
	printf("_part1_\n");
	if ((input = fopen("part1.dat","rb"))==NULL)
	{
		printf("Nao foi possivel abir o arquivo\n");
		exit(1);
	}
	rewind(input);
	fread(&aux, sizeof(int), 1, input); 
	while(feof(input)==0){			
		printf("%d ",aux);
		fread(&aux, sizeof(int), 1, input);
	}

	fclose(input);

	if ((input = fopen("part2.dat","rb"))==NULL)
	{
		printf("Nao foi possivel abir o arquivo\n");
		exit(1);
	}
	rewind(input);
	printf("\n\n");
	printf("_part2_\n");
	fread(&aux, sizeof(int), 1, input); 
	while(feof(input)==0){			
		printf("%d ",aux);
		fread(&aux, sizeof(int), 1, input);
	}
	fclose(input);

	printf("\n");
	return 0;
}
