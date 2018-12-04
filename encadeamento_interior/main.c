#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"

char* arquivo_cliente = "cliente.dat";
int x_mod = 7;

void reseta_clientes(){

    FILE *out;
    if ((out = fopen(arquivo_cliente,"wb+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo\n");
        exit(1);
    }
    else{
        printf("cliente.dat resetado com sucesso!\n");
        fclose(out);
    }
}

void insere(Cliente* cliente){

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }

    int pos_hash = cliente->cod % x_mod;
    int prox = pos_hash;

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

        pos_cliente_anterior = prox;

        fseek(file_cliente, pos_cliente_anterior * tamanho(), SEEK_SET);
        cliente_anterior = le(file_cliente);

        if(cliente_anterior != NULL){
            
            if(cliente_anterior->status == 1){

                eh_conflito = 1;
                if(cliente_anterior->status == 1 && cliente_anterior->cod == cliente->cod){
                    printf("Cliente com mesmo código já existente na tabela.\n");
                    fclose(file_cliente);
                    return;
                    //exit(1);
                }
            }
            else if(cliente_anterior->status == 0){
                
                if(achou_vazio == 0){
                    prox_do_vazio = cliente_anterior->prox;
                    achou_vazio = 1;
                    pos_vazia = prox;
                }
            }
       
            prox = cliente_anterior->prox;
            if(prox == 0){
                break;
            }
        }
        else{
            break;
        }
    }

    prox = pos_cliente_anterior;
    //return;

    // Se não achou vazio insere no final, atualiza o ponteiro do ultimo da lista;
    if(achou_vazio == 0){

        if(prox >= 6){
            printf("Tabela cheia não foi possível inserir %i\n", cliente->cod);
            return;
        }
        
        if(eh_conflito == 0){

            fseek(file_cliente, prox * tamanho(), SEEK_SET);
            salva(cliente, file_cliente);
            fflush(file_cliente);
            fclose(file_cliente);

            //unsigned long posicao_inserido = (ftell(file_cliente)/tamanho()) - 1;
            
        }
        else{

            FILE *file_cliente_atualizar;
            if ((file_cliente_atualizar = fopen(arquivo_cliente,"a+"))==NULL)
            {
                printf("Nao foi possivel abir o arquivo de clientes\n");
                exit(1);
            }
            else{

                salva(cliente, file_cliente_atualizar);
                fflush(file_cliente_atualizar);
                unsigned long posicao_inserido = (ftell(file_cliente_atualizar)/tamanho()) - 1;
                fclose(file_cliente_atualizar);

                cliente_anterior->prox = posicao_inserido;
                fseek(file_cliente, pos_cliente_anterior * tamanho(), SEEK_SET);
                salva(cliente_anterior, file_cliente);
                fflush(file_cliente);
                fclose(file_cliente);
            }
        }
        
    }
    else{ // Se achou vazio no caminho, ajusta o próximo do novo elemento e insere na posição antes vazia. 

        cliente->prox = prox_do_vazio;
        fseek(file_cliente, pos_vazia * tamanho(), SEEK_SET);
        salva(cliente, file_cliente);
        fflush(file_cliente);
        fclose(file_cliente);
    }
}

void le_lista_do_hash(int pos_hash){

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }

    int prox = pos_hash;

    while(prox != -1){

        fseek(file_cliente, prox * tamanho(), SEEK_SET);
        Cliente *c = le(file_cliente);

        if(c != NULL){
            if(c->status == 1){
                imprime(c);
            }

            prox = c->prox;
            free(c);
        }
        else{
            break;
        }

        if(prox == 0){
            break;
        }

      
    }

    fclose(file_cliente);
}

void buscar(int chave){

    int pos_hash = chave % x_mod;
    int prox = pos_hash;
    int encontrado = 0;

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }


    while(prox != -1){

        fseek(file_cliente, prox * tamanho(), SEEK_SET);
        Cliente *c = le(file_cliente);
        
        if(c != NULL){
            if(c->status == 1 && c->cod == chave){
                imprime(c);
                encontrado = 1;
                break;
            }
        
            prox = c->prox;
            free(c);
        }

        if(prox == 0){
            break;
        }
       
    }

    if(encontrado == 0){
        printf("Nenhum cliente com a chave %i encontrado\n", chave);
    }

    fclose(file_cliente);
}

void remover(int chave){

    int pos_hash = chave % x_mod;
    int prox = pos_hash;
    int encontrado = 0;

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r+"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        exit(1);
    }


    while(prox != -1){

        fseek(file_cliente, prox * tamanho(), SEEK_SET);
        Cliente *c = le(file_cliente);
        
        if(c != NULL){
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
        else{
            break;
        }
        
        if(prox == 0){
            break;
        }
    }

    if(encontrado == 0){
        printf("Nenhum cliente com a chave %i encontrado\n", chave);
    }

    fclose(file_cliente);
}

void ler_tabela_clientes(){

    FILE *file_cliente;
    if ((file_cliente = fopen(arquivo_cliente,"r"))==NULL)
    {
        printf("Nao foi possivel abir o arquivo de clientes\n");
        return;
    }

    printf("Lendo tabela cliente.dat\n");
    Cliente* c = NULL;
    fseek(file_cliente, 0, SEEK_SET);

    c = le(file_cliente);
    while(c != NULL){
        printf("Cliente %i\n", c->cod);
        c = le(file_cliente);
    }

    fclose(file_cliente);
}

void main(int argc, char** argv) {

    //Qualquer parametro a mais zera as tabelas
    if(argc >= 2){
        reseta_clientes();
    }


    //INICIO DOS TESTES
    Cliente* cliente1 = cliente(0, "MATHEUS");
    insere(cliente1);

    // //INICIO DO PRIMEIRO TESTE
    cliente1 = cliente(7, "MATHEUS");
    insere(cliente1);

    cliente1 = cliente(14, "MATHEUS");
    insere(cliente1);

    cliente1 = cliente(21, "MATHEUS");
    insere(cliente1);

    cliente1 = cliente(28, "MATHEUS");
    insere(cliente1);

    //INICIO DO SEGUNDO TESTE
    cliente1 = cliente(1, "MATHEUS");
    insere(cliente1);

    //INICIO DO TERCEIRO TESTE
    cliente1 = cliente(8, "MATHEUS");
    insere(cliente1);

    cliente1 = cliente(15, "MATHEUS");
    insere(cliente1);

   
    cliente1 = cliente(22, "MATHEUS");
    insere(cliente1);

    remover(7);


    // //INICIO DO QUINTO TESTE
    // cliente1 = cliente(5, "MATHEUS");
    // insere(cliente1);

    // cliente1 = cliente(6, "MATHEUS");
    // insere(cliente1);

    // //INICIO DO QUINTO TESTE
    // cliente1 = cliente(35, "MATHEUS");
    // insere(cliente1);

    // cliente1 = cliente(36, "MATHEUS");
    // insere(cliente1);

    // cliente1 = cliente(37, "MATHEUS");
    // insere(cliente1);

    
    ler_tabela_clientes();


    //buscar(7);
    //le_lista_do_hash(6);

    //remover(7);

    //buscar(21);
    

    //imprime(cliente1);


    //insere_agencia();
    //le_arquivo_agencia(arquivo_agencia);
}