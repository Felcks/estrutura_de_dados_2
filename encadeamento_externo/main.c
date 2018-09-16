#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

char* arquivo_cliente = "cliente.dat";
char* arquivo_hash = "compartimento_hash.dat";

void reseta_clientes(){

    FILE *out;
    if ((out = fopen(arquivo_cliente,"wb+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo\n");
        exit(1);
    }
    else{
        printf("cliente.dat resetado com sucesso!\n");
    }
}

void reseta_compartimento(){

    FILE *out;
    if ((out = fopen(arquivo_hash,"wb+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo\n");
        exit(1);
    }
    else{
        int vEntrada[7] = {-1, -1, -1, -1, -1, -1, -1};
        for (int i = 0; i < 7; i++)
        {
            fwrite(&vEntrada[i], sizeof(int), 1, out);
        }
        fflush(out);
    }

    printf("Escrevendo as entradas no arquivo (compartimento_hash.dat):\n");
    rewind(out);
    int i = 0;
    while (fread(&i, sizeof(int), 1, out) != 0) {
        printf("%i ",i);
    }
    printf("\n");

    fclose(out);
}

void insere(Cliente* cliente){

    FILE *out;
    if ((out = fopen(arquivo_hash,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de compartimento\n");
        exit(1);
    }

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"a+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }


    int pos_hash = cliente->cod % 7;
    int prox = 0;

    //Conferindo sem conflitos
    fseek(out, pos_hash * sizeof(int), SEEK_SET);
    fread(&prox, sizeof(int), 1, out);
    fflush(out);

    //Casos de conflitos
    Cliente* cliente_anterior = NULL;
    int pos_cliente_anterior = 0;
    int eh_conflito = 0;

    //Caso de achar alguém vazio no caminho;
    int pos_vazia = 0;
    int achou_vazio = 0;
    int prox_do_vazio = 0;
    
    while(prox != -1){
        
        free(cliente_anterior);

        eh_conflito = 1;
        pos_cliente_anterior = prox;

        fseek(file_cliente, pos_cliente_anterior * tamanho(), SEEK_SET);
        cliente_anterior = le(file_cliente);

        if(cliente_anterior->status == 1 && cliente_anterior->cod == cliente->cod){
            printf("Cliente com mesmo código já existente na tabela.\n");
            exit(1);
        }

        //Caso esteja alguém liberado no caminho -- FILE ta em a+ então isso nem rola pq né
        if(cliente_anterior->status == 0 && achou_vazio == 0){
            prox_do_vazio = cliente_anterior->prox;
            achou_vazio = 1;
            pos_vazia = prox;
        }
        
        prox = cliente_anterior->prox;
    }    

    // Se não achou vazio insere no final, atualiza o ponteiro do ultimo da lista;
    if(achou_vazio == 0){
        
        salva(cliente, file_cliente);
        fflush(file_cliente);
        unsigned long posicao_inserido = (ftell(file_cliente)/tamanho()) - 1;
        fclose(file_cliente);

        if(eh_conflito == 0){
            
            fseek(out, pos_hash * sizeof(int), SEEK_SET);
            fwrite(&posicao_inserido, sizeof(int), 1, out);
            fflush(out);
        }
        else{

            FILE *file_cliente_atualizar;
            if ((file_cliente_atualizar = fopen(arquivo_cliente,"r+"))==NULL)
            {
                printf("Nao foi possivel abir o arquivo de clientes\n");
                exit(1);
            }
            else{

                fseek(file_cliente_atualizar, pos_cliente_anterior * tamanho(), SEEK_SET);
                cliente_anterior->prox = posicao_inserido;
                salva(cliente_anterior, file_cliente_atualizar);
                fflush(file_cliente_atualizar);
                fclose(file_cliente_atualizar);
            }
        }
    }
    else{ // Se achou vazio no caminho, ajusta o próximo do novo elemento e insere na posição antes vazia. 

        FILE *file_cliente_atualizar;
        if ((file_cliente_atualizar = fopen(arquivo_cliente,"r+"))==NULL)
        {
            printf("Nao foi possivel abir o arquivo de clientes\n");
            exit(1);
        }
        else{

            cliente->prox = prox_do_vazio;
            fseek(file_cliente_atualizar, pos_vazia * tamanho(), SEEK_SET);
            salva(cliente, file_cliente_atualizar);
            fflush(file_cliente_atualizar);
            fclose(file_cliente_atualizar);
        }
    }
    
    fclose(out);
}

void le_lista_do_hash(int pos_hash){

    FILE *out;
    if ((out = fopen(arquivo_hash,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de compartimento\n");
        exit(1);
    }

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }

    int prox = 0;
    fseek(out, pos_hash * sizeof(int), SEEK_SET);
    fread(&prox, sizeof(int), 1, out);
    fflush(out);

    while(prox != -1){

        fseek(file_cliente, prox * tamanho(), SEEK_SET);
        Cliente *c = le(file_cliente);

        if(c->status == 1)
            imprime(c);
        
        prox = c->prox;
        free(c);
    }

    fclose(out);
    fclose(file_cliente);
}

void buscar(int chave){

    int pos_hash = chave % 7;
    int encontrado = 0;

    FILE *out;
    if ((out = fopen(arquivo_hash,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de compartimento\n");
        exit(1);
    }

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }

    int prox = 0;
    fseek(out, pos_hash * sizeof(int), SEEK_SET);
    fread(&prox, sizeof(int), 1, out);
    fflush(out);

    while(prox != -1){

        fseek(file_cliente, prox * tamanho(), SEEK_SET);
        Cliente *c = le(file_cliente);
        
        if(c->status == 1 && c->cod == chave){
            imprime(c);
            encontrado = 1;
            break;
        }
        
        prox = c->prox;
        free(c);
    }

    if(encontrado == 0){
        printf("Nenhum cliente com a chave %i encontrado\n", chave);
    }

    fclose(out);
    fclose(file_cliente);
}

void remover(int chave){

    int pos_hash = chave % 7;
    int encontrado = 0;

    FILE *out;
    if ((out = fopen(arquivo_hash,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de compartimento\n");
        exit(1);
    }

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }

    int prox = 0;
    fseek(out, pos_hash * sizeof(int), SEEK_SET);
    fread(&prox, sizeof(int), 1, out);
    fflush(out);

    while(prox != -1){

        fseek(file_cliente, prox * tamanho(), SEEK_SET);
        Cliente *c = le(file_cliente);
        
        if(c->status == 1 && c->cod == chave){
            printf("Cliente de chave %i removido\n", chave);

            c->status = 0;
            fseek(file_cliente, prox * tamanho(), SEEK_SET);
            salva(c, file_cliente);
            encontrado = 1;
            break;
        }
        
        prox = c->prox;
        free(c);
    }

    if(encontrado == 0){
        printf("Nenhum cliente com a chave %i encontrado\n", chave);
    }

    fclose(file_cliente);
    fclose(out);
}

void main(int argc, char** argv) {

    //Qualquer parametro a mais zera as tabelas
    if(argc >= 2){
        reseta_compartimento();
        reseta_clientes();
    }


    Cliente* cliente1 = cliente(1, "MATHEUS");
    insere(cliente1);

    //buscar(7);
    //le_lista_do_hash(0);

    //remover(7);

    //buscar(15);
    

    //imprime(cliente1);


    //insere_agencia();
    //le_arquivo_agencia(arquivo_agencia);
}