#include <stdlib.h>
#include <stdio.h>
#include "cliente.h"

int main(int argc, char const *argv[])
{
	
    printf("\n\nLendo funcionários do arquivo...\n\n");
    Cliente *f;
    FILE *out;
    //54
    out=fopen("saida.dat","rb");
    rewind(out);
    int i=0;
    while ((f = le(out)) != NULL) {
        imprime(f);
        free(f);
        i++;
    }
    printf("\n%d\n",i );
	return 0;
}