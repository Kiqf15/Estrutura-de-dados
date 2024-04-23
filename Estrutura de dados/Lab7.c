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

int isEmpty(Pilha *pilha){
    return pilha ->qtde == 0;
}

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
    novo->anterior = pilha->topo;
    pilha->topo = novo;
    pilha->qtde++;
    
}

int pop(Pilha *pilha){
    if(pilha->qtde > 0){
        int valor = pilha->topo->valor;
        Celula *libera = pilha->topo;
        pilha->topo = pilha->topo->anterior;
        pilha->qtde--;
        free(libera);
        return valor;
    }
    else{
        return -1;
    }
}

Pilha *inicializar_pilha(){
    Pilha *pilha = malloc(sizeof(Pilha));
    pilha->topo = NULL;
    pilha->qtde = 0;
    return pilha;
}

int main(void) {
    Pilha *pilha = inicializar_pilha();
    char expr[100];
    fgets(expr, sizeof(expr), stdin);

    for (int i = 0; i < sizeof(expr) && expr[i] != '\0'; i++) {
        
        if (expr[i] == '{' || expr[i] == '[' || expr[i] == '(') 
        {
            push(pilha, expr[i]);
            if ((expr[i] == '{' && 
            pilha->topo->anterior->valor == '[') || 
            (expr[i] == '{' &&
            pilha->topo->anterior->valor == '(')|| 
            (expr[i] == '[' && 
            pilha->topo->anterior->valor == '('))
            {
                printf("incorreto");
                return 0;
            }
        } 
        else if (expr[i] == '}' || expr[i] == ']' || expr[i] == ')') {
            if (!isEmpty(pilha)) {
                int top = pop(pilha);
                if ((expr[i] == '}' && top != '{') ||
                    (expr[i] == ']' && top != '[') ||
                    (expr[i] == ')' && top != '(')) {
                    printf("incorreto");
                    return 0;
                }
            } else {
                printf("incorreto");
                return 0;
            }
        }
    }

    if (isEmpty(pilha)) {
        printf("correto");
    } else {
        printf("incorreto");
    }

    return 0;
}