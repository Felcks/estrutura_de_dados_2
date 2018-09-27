#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cliente.h"
#include "fila.h"

char nomeRes[10];
int contador = 0;
int qntArquivos;
int qntEntradas=7;
int contE, contD;
int qntFolhas;
Lista *ultimaLista;

struct Arvore {
    Cliente *cliente;
    FILE *arquivo;

    struct Arvore *pai;
    struct Arvore *esq;
    struct Arvore *dir;
}; 
typedef struct Arvore Arvore;

Arvore *vencedores;

Arvore* insereArvore (Arvore *nova, FILE *a, Arvore *esq, Arvore *dir) {
    nova = (Arvore*)malloc(sizeof(Arvore));
    if((esq==NULL)&&(dir==NULL)){
        Cliente *cliente; 
        cliente = le(a);
        nova->cliente = cliente;
    }
    
    //cria pai copia da folha menor
    else if (esq->cliente->cod <= dir->cliente->cod){
        nova->cliente = esq->cliente;
    }
    else if (dir->cliente->cod <= esq->cliente->cod){
        nova->cliente = dir->cliente;
    }
    nova->esq = esq;
    nova->arquivo = a;
    nova->dir = dir;
    nova->pai=NULL;
    if (dir != NULL)
    {
        esq->pai=nova;
        dir->pai=nova;
    }
    return nova;
}

Arvore *liberaMenor(){
    Arvore *b;
    b=vencedores; 
    while(b->esq!=NULL){
       if ((b->esq->cliente!=NULL)&&(b->esq->cliente->cod == b->cliente->cod)){
            b->cliente==NULL;
            b=b->esq;
        }
        else if ((b->dir->cliente!=NULL)&&(b->dir->cliente->cod == b->cliente->cod)){
           b->cliente==NULL;
           b=b->dir;
        }
    }
    vencedores->cliente=NULL;
    return b;
}

void liberaArvore (Arvore *a){
    if (a != NULL){
        liberaArvore(a->esq);
        liberaArvore(a->dir);
        free(a);
    }
}

void insereLista(Fila *f,Lista *l1){
    Lista *lArmazena = (Lista*)malloc(sizeof(Lista));
    strcpy(lArmazena->nome,l1->nome);
    lArmazena->input = l1->input;
    lArmazena->prox = NULL;
    if (f->inicio==NULL){
        f->inicio = lArmazena;
    }
    else if(f->fim != NULL){
        f->fim->prox = lArmazena;
    }
    else{
        f->inicio = lArmazena;
    }

    f->fim = lArmazena;
} 

Arvore *menor(Arvore *a, Arvore *b){
    Arvore *menor;
    if (a->cliente->cod <= b->cliente->cod){
        menor = insereArvore(menor, a->arquivo, a, b);
    }
    else if (b->cliente->cod <= a->cliente->cod){
        menor = insereArvore(menor, b->arquivo, a, b);
    }
    return menor;
}

Arvore *criaGalho(Lista *lArquivosAbertos){
    // cria duas folhas e retorna o pai com a copia da menor
    Arvore *a1;
    a1 = insereArvore(a1,lArquivosAbertos->input,NULL,NULL);
    Arvore *a2;
    if (lArquivosAbertos->prox==NULL){
    }
    a2 = insereArvore(a2,lArquivosAbertos->prox->input,NULL,NULL);
    Arvore *menor1;
    menor1 = menor(a1, a2);
    return menor1;    
}

Arvore *criaRamo(Lista *lArquivosAbertos, int cont){
    //se for ramo esq
    if (cont==contE){
        Arvore *menor1;
        menor1 = criaGalho(lArquivosAbertos);
        contE=contE-2;
        ultimaLista = lArquivosAbertos->prox->prox;
        
        if(contE>0){
            Arvore *menor2;
            menor2 = menor(menor1,criaGalho(lArquivosAbertos->prox->prox));
            contE=contE-2;
            
            if (contE==0){
                ultimaLista = lArquivosAbertos->prox->prox->prox->prox;
                
                return menor2;
            }
            
            else if (contE>0){
                Arvore *menor3;
                int cont1=contE;
                menor3 = menor(menor2, criaRamo(lArquivosAbertos->prox->prox, cont1));
                
                if (contE==0){
                    ultimaLista = lArquivosAbertos->prox->prox->prox->prox;
                    
                    return menor3;
                }
            }
        }
        if (contE==0){
            ultimaLista = lArquivosAbertos->prox->prox;
            
            return menor1;
        }
    }
    //se for ramo dir
    else if (cont==contD){
        
        if (contD>1){
            Arvore *menor1;
            menor1 = criaGalho(lArquivosAbertos);
            contD=contD-2;
           
            if(contD>1){
                Arvore *menor2;
                menor2 = menor(menor1,criaGalho(lArquivosAbertos->prox->prox));
                contD=contD-2;
                
                if (contD==1){
                    Arvore *a1;
                    a1 = insereArvore(a1,lArquivosAbertos->prox->prox->prox->prox->input,NULL,NULL);
                    
                    return menor(menor2,a1);
                }
               
                if (contD>1){
                    Arvore *menor3;
                    int cont2 = contD;
                    menor3 = menor(menor2, criaRamo(lArquivosAbertos->prox->prox, cont2));
                   
                    if (contD==1){
                        Arvore *a1;
                        a1 = insereArvore(a1,lArquivosAbertos->prox->prox->prox->prox->input,NULL,NULL);
                     
                        return menor(menor3,a1);
                    }
                }
            }
            if (contD==1){
                Arvore *a2;
                a2 = insereArvore(a2,lArquivosAbertos->prox->prox->input,NULL,NULL);
                     
                return menor(menor1,a2);
            }
            
            if (contD==0){
                return menor1;
            }

        }
        //retorna folha se o ramo só tiver uma folha
        else if (contD==1){
            Arvore *a1;
            a1 = insereArvore(a1,lArquivosAbertos->input,NULL,NULL);          
            
            return a1;
           
        }
    }

}
Arvore *montaArv(Lista *lArquivosAbertos, FILE *out, Arvore *esq,Arvore *dir, int qntFolhas){
    int multiplo = qntFolhas/2;
    int restoMultiplo = multiplo%2;
    //conta folhas que tem q ser criadas na dir e esq
    int qntFolhasE;
    int qntFolhasD;
    int cont;

    //verificar se é multiplo de 4 +1
    if((qntFolhas-1)%4==0){
        qntFolhasE = (multiplo + restoMultiplo)*2;
        qntFolhasD = (qntFolhas - qntFolhasE);
        contE = qntFolhasE;
        contD = qntFolhasD;              
            
    }
    else{
        qntFolhasE = (multiplo + restoMultiplo);
        qntFolhasD = (qntFolhas - qntFolhasE);
        contE = qntFolhasE;
        contD = qntFolhasD;             
    }

    //se arvore só tem dus folhas
    if (qntFolhas == 2){
        qntFolhasD=qntFolhasE;
        qntFolhasE=999;
        contD=qntFolhasD; 
        cont=contD;

        Arvore *ramoD = criaRamo(lArquivosAbertos, cont);

        return ramoD;
    }
    

   //ramo es1
    cont = contE;
    Arvore *ramoE = criaRamo(lArquivosAbertos,cont);
   
    //ramo dir
    cont=contD;
    Arvore *ramoD = criaRamo(ultimaLista, cont);

    return menor(ramoE,ramoD);
}

void compara(Arvore *a){
    while(vencedores->cliente==NULL){
        
        //se um dos arquivos chegou ao fim  
        if ((feof(a->dir->arquivo)!=0)||(feof(a->esq->arquivo)!=0)){
          
            //se arq da esquerda acabou e nao tiver clientes sobe o da direita
            if((feof(a->esq->arquivo)!=0)&&(a->esq->cliente==NULL)){
                a->cliente=a->dir->cliente;
                a->arquivo=a->dir->arquivo;
            }
            else if((feof(a->dir->arquivo)!=0)&&(a->dir->cliente==NULL)){
               a->cliente=a->esq->cliente;
               a->arquivo=a->esq->arquivo;
            }     
        }
        //se cod do cliente da esquerda menor sobe o da esq
        else if((a->esq->cliente->cod)<=(a->dir->cliente->cod)){
            a->cliente=a->esq->cliente;
            a->arquivo=a->esq->arquivo;
        }
        else if((a->esq->cliente->cod)>(a->dir->cliente->cod)){
            a->cliente=a->dir->cliente;
            a->arquivo=a->dir->arquivo;
        }
        a=a->pai;
    }
}

int main(){
    //raiz da arvore de vencedores
    vencedores = (Arvore*)malloc(sizeof(Arvore));
    FILE *out;

    scanf("%d",&qntArquivos);

    //scanf("%d",&qntEntradas);
    //char nomeEntradas[10];

    char nomeSaida[10]="saida.dat";

    //fila de part
    Fila *f = criaFila();

 //    for(int i=0; i<qntEntradas; i++) {
 //        scanf("%s",&nomeEntradas);
 //        insere(f, nomeEntradas);
 //    }

    //insere part na fila
    insere(f, "ent0.dat");
    insere(f, "ent1.dat");
    insere(f, "ent2.dat");
    insere(f, "ent3.dat");
    insere(f, "ent4.dat");
    insere(f, "ent5.dat");
    insere(f, "ent6.dat");

    //fila de arquivos abertos
    Fila *lArquivosAbertos = criaFila();
    
    for (int i = 0; i < qntArquivos-1; i++){           
        f->inicio->input = fopen(f->inicio->nome, "rb");
        
        insereLista(lArquivosAbertos,f->inicio);
        retira(f);
    }

    snprintf (nomeRes, sizeof(nomeRes), "res%d.dat", contador);
    qntFolhas = qntArquivos-1;
    
    while((lArquivosAbertos->inicio!=NULL)){
        out=fopen(nomeRes,"w+b");
        
        vencedores = montaArv(lArquivosAbertos->inicio,out,NULL,NULL,qntFolhas);
        salva(vencedores->cliente,out);
        Arvore *removida;
       
       int verifica=0;
        
        while((verifica!=1)||(removida->cliente!=NULL)){
            removida = liberaMenor();
            removida->cliente = le(removida->arquivo);
            Lista *correr = lArquivosAbertos->inicio;
            
            verifica=1;
            
            while((correr!=NULL)&&(verifica==1)){
                if (feof(correr->input)==0){
                    verifica=0;
                }
            
                else if (feof(correr->input)!=0){
                    verifica=1;
                }
            
                correr = correr->prox;

            }
            
            if ((verifica!=1)||(removida->cliente!=NULL)){
                compara(removida->pai);
                salva(vencedores->cliente,out);
            }
        }
        
        for (int i = 0; i < qntArquivos-1; i++){
            if (lArquivosAbertos->inicio!=NULL){
                fclose(lArquivosAbertos->inicio->input);
                retira(lArquivosAbertos);

            }
           
        }
        
        insere(f, nomeRes);
        
        //cria o nome do arquivo de saida e fecha o anterior
        contador++;
        snprintf (nomeRes, sizeof(nomeRes), "res%d.dat", contador);
        fclose(out);

        //retita part da fila abre os arquivos e joga para lista de abertos
        //muda qnt de folhas se qntPart < qnt de arquivos simultaneos
        for (int i = 1; ((i < qntArquivos)&&(f->inicio!=NULL)); i++){  
            f->inicio->input = fopen(f->inicio->nome, "rb");
            insereLista(lArquivosAbertos,f->inicio);
     
            if ((f->inicio==f->fim)&&(i<(qntEntradas-1))){
               qntFolhas=i;
               i=qntArquivos;         
            }            
            retira(f);
        }
    }

    //copia ultimo parti ordenada para saida.dat
    snprintf (nomeRes, sizeof(nomeRes), "res%d.dat", contador-1);
    FILE *ultimo = fopen(nomeRes, "rb");
    rewind(ultimo);
    FILE *saida = fopen(nomeSaida, "w+b");
    
    Cliente *client;
    while(feof(ultimo)==0){
        client = le(ultimo);
        if (feof(ultimo)==0){
            salva(client,saida);
        }
    }
    free(client);

    free(lArquivosAbertos);

    
    return 0;
}


