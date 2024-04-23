#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//definição lista dinamica encadeada
typedef struct Paciente {
    char *nome;
    int RG;
    int idade;
    char *entrada; //formato DDMMYYYY
    struct Paciente *proximo;
} Paciente;

typedef struct Lista {
    int qtde;
    Paciente *primeiro;
} Lista;

Lista *inicializa_lista() {
    Lista *l = malloc(sizeof(Lista));
    l->primeiro = NULL;
    l->qtde = 0;
    return l;
}

int atualizar_paciente(Lista *l, int RG, char *novo_nome, int nova_idade, char *nova_entrada) {
    Paciente *atual = l->primeiro;
    while (atual != NULL) {
        if (atual->RG == RG) {
            free(atual->nome); // Liberar a memória do nome antigo
            atual->nome = strdup(novo_nome); // Atualizar o nome
            atual->idade = nova_idade; // Atualizar a idade
            atual->entrada = strdup(nova_entrada); // Atualizar a entrada
            return 1; // Retornar 1 se o paciente foi atualizado com sucesso
        }
        atual = atual->proximo;
    }
    return 0; // Retornar 0 se o paciente não for encontrado
}


void inserir_paciente(Lista *l, char *nome, int RG, int idade, char *entrada) {
    Paciente *novo = malloc(sizeof(Paciente));
    //strcpy(novo->nome, nome);
    novo->nome = strdup(nome);
    novo->RG = RG;
    novo->idade = idade;
    novo->entrada = strdup(entrada);
    novo->proximo = NULL;
    //caso seja o primeiro paciente a ser inserido
    if (l->primeiro == NULL) {
        l->primeiro = novo;
    } 
    else {
        Paciente *atual = l->primeiro;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
    l->qtde++;
}

Paciente* buscar_paciente(Lista *l, int RG) {
    Paciente *atual = l->primeiro;
    while (atual != NULL) {
        if (atual->RG == RG) {
            // Encontrou o paciente com o RG correspondente
            printf("\n\nDados encontrados:\n\nNome: %s\nRG: %d\nIdade: %d\nEntrada: %s\n\n", atual->nome, atual->RG, atual->idade, atual->entrada);
            return atual;
        }
        //passa pro proximo paciente
        atual = atual->proximo;
    }
    // Não encontrou o paciente com o RG fornecido
    return NULL; 
}

int remover_paciente(Lista *l, int RG) {
    // Assume-se que a lista não está vazia e que o paciente com o RG fornecido existe

    Paciente *atual = l->primeiro;
    Paciente *anterior = NULL;

    // Encontrar o paciente e o anterior a ele
    while (atual != NULL && atual->RG != RG) {
        anterior = atual;
        atual = atual->proximo;
    }

    // Se o paciente não for o primeiro na lista
    if (anterior != NULL) {
        anterior->proximo = atual->proximo; // Retira o paciente da lista
    } else {
        // Se o paciente a ser removido é o primeiro da lista
        l->primeiro = atual->proximo;
    }
    // Libera a memória do nome do paciente
    free(atual->nome); 
    // Libera a memória do paciente
    free(atual); 
    // Decrementa o contador de pacientes na lista
    l->qtde--; 

    return 1; // Retorna sucesso
}


void imprimir_pacientes(Lista *l) {
    system("cls");
    printf("START\n\n");
    Paciente *atual = l->primeiro;
    while (atual != NULL) {
        printf("%s, %d, %d, %s\n", atual->nome, atual->RG, atual->idade, atual->entrada);
        atual = atual->proximo;
    }
    printf("\nEND - TOTAL DA LISTA = %d\n", l->qtde);
}

//=================================================


// Carregar e salvar arquivos
void cadastrarTxt(Lista *l){
    //caso lista vazia
    if (l->primeiro == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    //pega primeiro da lista
    Paciente *atual = l->primeiro;
    //tenta abrir arquivo, e caso não exista já o inicializa
    FILE *infoPacientes = fopen("dados_pacientes.txt","a");
    while (atual != NULL){
        fprintf(infoPacientes,"%s %d %d %s\n", atual->nome, atual->RG, atual->idade, atual->entrada);
        atual = atual->proximo;
    }
    fclose(infoPacientes);
    printf("Adicionado!\n");
}

//função ler arquivo
void lerTxt(Lista *l) {
    FILE *dados = fopen("dados_pacientes.txt", "r");
    if (dados == NULL) {
        printf("Nao existem dados registrados no arquivo!\n");
        return;
    }

    char nome[255];  // Ajuste o tamanho conforme necessário
    int rg, idade;
    char entrada[255];  // Supondo que entrada seja uma data ou string

    while (fscanf(dados, "%s %d %d %s", nome, &rg, &idade, entrada) == 4) {
        inserir_paciente(l, nome, rg, idade, entrada);

        // Imprime os dados do paciente lido no terminal
        printf("Paciente: %s, RG: %d, Idade: %d, Entrada: %s\n", nome, rg, idade, entrada);
    }
    fclose(dados);
}



//=================================================

//definiçao da Fila dinamica
typedef struct CelAtend {
  char *nome;
  int RG;
  int idade;
  char *entrada;
  struct CelAtend *proximo;
  struct CelAtend *anterior;
} CelAtend;

typedef struct {
  CelAtend *head;
  CelAtend *tail;
  int qtde;
} Fila;

CelAtend *cria_celula(char *nome, int RG, int idade, char *entrada) {
  CelAtend *celula = malloc(sizeof(CelAtend));
  celula->proximo = NULL;
  celula->anterior = NULL;
  celula->nome = strdup(nome);
  celula->RG = RG;
  celula->idade = idade;
  celula->entrada = strdup(entrada);
  
  return celula;
}

Fila *cria_queue() {
  Fila *queue = malloc(sizeof(Fila));
  queue->head = NULL;
  queue->tail = NULL;
  queue->qtde = 0;

  return queue;
}

void enqueue(Fila *queue, char *nome, int RG, int idade, char *entrada) {
  CelAtend *nova = cria_celula(nome, RG, idade, entrada);
  if (queue->head == NULL) {
    queue->head = queue->tail = nova;
  } else {
    nova->anterior = queue->tail;
    queue->tail->proximo = nova;
    queue->tail = nova;
  }
  queue->qtde++;
  printf("Paciente enfileirado com sucesso!\n");
}

int dequeue(Fila *queue) {
//caso fila vazia
  if (queue->tail == NULL) {
    return -1;
  } 
  //primeiro paciente da fila
  CelAtend *atual = queue->head;
  //caso somente uma pessoa na fila
  if (queue->head == queue->tail) {
    queue->head = NULL;
    queue->tail = NULL;
    } 
    else {
      //queue->tail = queue->head->anterior;
      //queue->tail->proximo = NULL;
      queue->head = atual->proximo;
      queue->head->anterior = NULL;
    }
  queue->qtde--;
  free(atual);
  printf("Paciente desenfileirado com sucesso!\n");
  //return valor;
}

void mostra_fila(Fila *queue) {
    CelAtend *atual = queue->head;
    printf("Pacientes em espera:\n\n");
    while (atual != NULL) {
        printf("%s, %d, %d, %s\n", atual->nome, atual->RG, atual->idade, atual->entrada);
        atual = atual->proximo;
    }
    printf("\n");
}

//=================================================
// Definição de arvore binária de busca

typedef struct EABB {
    char *nome;
    int idade;
    char *entrada; // formato DD-MM-YYYY
    struct EABB *esquerda, *direita;
} EABB;

typedef struct ABB {
    int qtde;
    EABB *raiz;
} ABB;

ABB* inicializar_arvore() {
    ABB *arvore = (ABB*)malloc(sizeof(ABB));
    if (arvore == NULL) {
        fprintf(stderr, "Erro ao alocar memória para a árvore.\n");
        return NULL;
    }
    arvore->qtde = 0;
    arvore->raiz = NULL;
    return arvore;
}

int extrair_ano(char *data) {
    // A data está no formato DD-MM-YYYY, então o ano começa no índice 6
    char ano[5];
    strncpy(ano, data + 6, 4);
    ano[4] = '\0';
    //converte para Int
    return atoi(ano);
}

int extrair_mes(char *data) {
    // A data está no formato DD-MM-YYYY, então o mês está nos índices 3 e 4
    char mes[3];
    strncpy(mes, data + 3, 2);
    mes[2] = '\0';
    //converte para Int
    return atoi(mes);
}

int extrair_dia(char *data) {
    // A data está no formato DD-MM-YYYY, então o dia está nos primeiros dois índices
    char dia[3];
    strncpy(dia, data, 2);
    dia[2] = '\0';
    //converte para Int
    return atoi(dia);
}

// Função para coletar os nós em uma lista
void coletar_nos(EABB *raiz, EABB ***lista, int *tamanho) {
    if (raiz != NULL) {
        coletar_nos(raiz->esquerda, lista, tamanho);
        
        // Redimensionar a lista para adicionar um novo elemento
        *lista = realloc(*lista, (*tamanho + 1) * sizeof(EABB*));
        (*lista)[*tamanho] = raiz;
        (*tamanho)++;
        
        coletar_nos(raiz->direita, lista, tamanho);
    }
}

// Comparador para ordenar por ano
int comparar_por_ano(const void *a, const void *b) {
    EABB *noA = *(EABB**)a;
    EABB *noB = *(EABB**)b;
    int anoA = extrair_ano(noA->entrada);
    int anoB = extrair_ano(noB->entrada);
    return anoA - anoB;
}

// Comparador para ordenar por mes
int comparar_por_mes(const void *a, const void *b) {
    EABB *noA = *(EABB**)a;
    EABB *noB = *(EABB**)b;
    int mesA = extrair_mes(noA->entrada);
    int mesB = extrair_mes(noB->entrada);
    return mesA - mesB;
}

// Comparador para ordenar por dia
int comparar_por_dia(const void *a, const void *b) {
    EABB *noA = *(EABB**)a;
    EABB *noB = *(EABB**)b;
    int diaA = extrair_dia(noA->entrada);
    int diaB = extrair_dia(noB->entrada);
    return diaA - diaB;
}

// Comparador para ordenar por idade
int comparar_por_idade(const void *a, const void *b) {
    EABB *noA = *(EABB**)a;
    EABB *noB = *(EABB**)b;
    return noA->idade - noB->idade;
}

// Função para exibir a lista de nós ordenados por ano
void exibir_ordenado_por_ano(EABB *raiz) {
    EABB **lista = NULL;
    int tamanho = 0;
    coletar_nos(raiz, &lista, &tamanho);

    qsort(lista, tamanho, sizeof(EABB*), comparar_por_ano);

    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s, Idade: %d, Entrada: %s\n", lista[i]->nome, lista[i]->idade, lista[i]->entrada);
    }

    free(lista);
}

// Função para exibir a lista de nós ordenados por mes
void exibir_ordenado_por_mes(EABB *raiz) {
    EABB **lista = NULL;
    int tamanho = 0;
    coletar_nos(raiz, &lista, &tamanho);

    qsort(lista, tamanho, sizeof(EABB*), comparar_por_mes);

    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s, Idade: %d, Entrada: %s\n", lista[i]->nome, lista[i]->idade, lista[i]->entrada);
    }

    free(lista);
}

// Função para exibir a lista de nós ordenados por dia
void exibir_ordenado_por_dia(EABB *raiz) {
    EABB **lista = NULL;
    int tamanho = 0;
    coletar_nos(raiz, &lista, &tamanho);

    qsort(lista, tamanho, sizeof(EABB*), comparar_por_dia);

    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s, Idade: %d, Entrada: %s\n", lista[i]->nome, lista[i]->idade, lista[i]->entrada);
    }

    free(lista);
}

// Função para exibir a lista de nós ordenados por idade
void exibir_ordenado_por_idade(EABB *raiz) {
    EABB **lista = NULL;
    int tamanho = 0;
    coletar_nos(raiz, &lista, &tamanho);

    qsort(lista, tamanho, sizeof(EABB*), comparar_por_idade);

    for (int i = 0; i < tamanho; i++) {
        printf("Nome: %s, Idade: %d, Entrada: %s\n", lista[i]->nome, lista[i]->idade, lista[i]->entrada);
    }

    free(lista);
}

// Função auxiliar para criar um novo nó
EABB* criar_novo_no(char *nome, int idade, char *entrada) {
    EABB *novo_no = (EABB*)malloc(sizeof(EABB));
    novo_no->nome = strdup(nome);
    novo_no->idade = idade;
    novo_no->entrada = strdup(entrada);
    novo_no->esquerda = novo_no->direita = NULL;
    return novo_no;
}

// Função auxiliar para inserir um nó, definida como static
static EABB* inserir_no(EABB *raiz, char *nome, int idade, char *entrada) {
    if (raiz == NULL) return criar_novo_no(nome, idade, entrada);

    if (idade < raiz->idade)
        raiz->esquerda = inserir_no(raiz->esquerda, nome, idade, entrada);
    else if (idade > raiz->idade)
        raiz->direita = inserir_no(raiz->direita, nome, idade, entrada);
    // Você pode decidir o que fazer se idade == raiz->idade

    return raiz;
}

// Função para inserir um novo nó na árvore
void inserir(ABB *arvore, char *nome, int idade, char *entrada) {
    if (arvore == NULL) {
        fprintf(stderr, "Árvore não inicializada.\n");
        return;
    }

    arvore->raiz = inserir_no(arvore->raiz, nome, idade, entrada);
    arvore->qtde++;
}

void inserir_pacientes_na_arvore(ABB *arvore, Lista *lista) {
    if (arvore == NULL) {
        fprintf(stderr, "Árvore não inicializada.\n");
        return;
    }

    if (lista == NULL || lista->primeiro == NULL) {
        fprintf(stderr, "Lista de pacientes vazia ou não inicializada.\n");
        return;
    }

    Paciente *atual = lista->primeiro;
    while (atual != NULL) {
        inserir(arvore, atual->nome, atual->idade, atual->entrada);
        atual = atual->proximo;
    }
}

//libera memoria da arvore
void liberar_arvore(EABB *raiz) {
    if (raiz == NULL) return;

    liberar_arvore(raiz->esquerda);
    liberar_arvore(raiz->direita);

    free(raiz->nome);  
    free(raiz->entrada);
    free(raiz);
}

//reseta arvore para os valores iniciais (raiz nula e qtd 0)
void resetar_arvore(ABB *arvore) {
    if (arvore == NULL) {
        fprintf(stderr, "Árvore não inicializada.\n");
        return;
    }

    liberar_arvore(arvore->raiz); 
    arvore->raiz = NULL;          
    arvore->qtde = 0;             
}

