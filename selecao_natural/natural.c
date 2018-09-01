#include <stdio.h>
#include <stdlib.h>
int contador = 0;

int cmp (const void * a, const void * b) {
   if ((int*)a == NULL)return 1;
   if ((int*)b == NULL)return -1;

   return ( *(int*)a - *(int*)b );
}

void ordena(FILE *input, int *v, int registro){
	
	FILE *out;
	char nomeArq[100];
	int reservatorio[7], j=0;
	int aux = registro;	
	snprintf (nomeArq, sizeof(nomeArq), "part%d.dat", contador);
	contador++;
	for (int i = 0; i < 7; i++)
	{
		reservatorio[i] = NULL;
	}
	
	if ((out = fopen(nomeArq,"wb+"))==NULL)
	{
		printf("Nao foi possivel abir o arquivo\n");
		exit(1);
	}
	if (contador >= 5)
	{
		printf("contador %d\n", contador);
		exit(1);
	}
		
	qsort(v, 7, sizeof(int), cmp);
	fwrite(&v[0],sizeof(int),1, out);
	//printf("%d\n",v[0] );

	for(int i = 0; i!=-1; i)
	{
		if (aux<v[0])
		{
			do
			{
				if ((aux>0))
				{
					reservatorio[j] = aux;
				}
				j++;
				fread(&aux,sizeof(int),1, input);
				if ((reservatorio[6]!=NULL)||(feof(input))){
					i=-1;
					break;
				}			
			}while(aux<v[0]);
		}	
		
		if (aux>v[0])
		{
			v[0]=aux;
		}

		if ((reservatorio[6]!=NULL)||(feof(input)==1)){
			i=-1;
			break;
		}
		
		qsort(v, 7, sizeof(int), cmp);
		fwrite(&v[0],sizeof(int),1, out);
		//printf("%d\n",v[0] );
		fread(&aux,sizeof(int),1, input);
	}
	if ((reservatorio[6] != NULL)||(feof(input)==1))
	{
		qsort(v, 7, sizeof(int), cmp);
		for (int i = 0; i < 6; i++)
		{
			if (v[i+1]>0)
			{
				fwrite(&v[i+1],sizeof(int),1, out);
				//printf("%d\n",v[i+1] );
			}
			
		}
		
	}
	if (reservatorio[0]==NULL){
		fclose(out);
		return;
	}
	fclose(out);
	ordena(input,reservatorio,aux);
}

int main(int argc, char const *argv[])
{
	FILE *input;
	if ((input = fopen("entrada.dat","rb"))==NULL)
	{
		printf("Nao foi possivel abir o arquivo\n");
		exit(1);
	}
	rewind(input);
	int vMemoria[7];
	fread(&vMemoria[0],sizeof(int), 7, input);
	
	int aux;
	fread(&aux,sizeof(int),1, input);

	ordena(input, vMemoria, aux);

	fclose(input);
	return 0;
}