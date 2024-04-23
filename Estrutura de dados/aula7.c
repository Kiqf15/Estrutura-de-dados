#include <stdio.h>
#include <stdlib.h>

typedef struct Celula{
    struct Celula *anterior;
    struct Celula *proximo;
    int valor;
}Celula;

typedef struct{
    Celula *topo;
    int qtde;
}Pilha;

Celula *inicializar_celula(int valor){
    Celula *novo = malloc(sizeof(Celula));
    novo->anterior = NULL;
    novo->proximo = NULL;
    novo->valor = valor;
    return novo;
}

void push(Pilha *pilha, int valor){
    //inicializa celula a ser inserida na pilha
    Celula *novo = inicializar_celula(valor);
    //caso nao vazia
    if(pilha->qtde !=0){
        pilha->topo->anterior = novo;
        novo->proximo = pilha->topo;
    }
    //caso vazia
    pilha->topo = novo;
    pilha->qtde++;
    
}

int pop(Pilha *pilha){
    if(pilha->qtde > 0){
        int valor = pilha->topo->valor;
        Celula *libera = pilha->topo;
        pilha->topo = pilha->topo->proximo;
        if(pilha->topo != NULL){
            pilha->topo->anterior = NULL;
        }
        pilha->qtde--;
        free(libera);
        return valor;
    }
    else{
        return -1;
    }
}

void imprimir(Pilha *pilha){
    Celula *atual = pilha->topo;
    printf("Topo -> ");
    while(atual != NULL){
        printf("%d ", atual->valor);
        atual = atual->proximo;
    }
    printf(" <- Base\n");
}

Pilha *inicializar_pilha(){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    pilha->qtde = 0;
    return pilha;
}

int main(void){
    Pilha *pilha = inicializar_pilha();
    for(int i = 1; i < 10; i++){
        push(pilha, i);
        imprimir(pilha);
    }
    for(int i = 0; i <=10; i++){
        pop(pilha, i);
        imprimir(pilha);
    }
}