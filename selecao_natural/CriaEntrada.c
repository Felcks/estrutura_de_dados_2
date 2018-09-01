#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{

	FILE *out;
	if ((out = fopen("entrada.dat","wb+"))==NULL)
	{
		printf("Nao foi possivel abir o arquivo\n");
		exit(1);
	}
	else{
		int vEntrada[24] = {30,14,15,75,32,6,5,81,48,41,87,18,56,20,26,4,21,65,22,49,11,16,8,12};
		for (int i = 0; i < 24; i++)
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
	return 0;
}

