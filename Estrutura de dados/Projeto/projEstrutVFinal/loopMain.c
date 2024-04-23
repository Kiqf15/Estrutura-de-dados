//importando conio.h para usar as funções kbhit() &  getch()
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "navegacao.c"
#include "estruturas.c"
/*
Alunos:
Matheus Miranda Vieira , RA: 222200172
Kaique da Silva Fernandes , RA: 22221011-4
Nicolas Costa Coppola de Moraes , RA: 22122099-9 
*/

//contador do menu, para identidicar aonde devo imprimir a seta
int menuMain = 0;
int menuCadastrar = 0;
int menuAtendimento = 0;
int menuPesquisa = 0;
int menuCarregarSalvar = 0;

//função cadastrar
int cadastrar(Lista *l){
    
    imprimeMenuCadastrar(menuCadastrar);
    while (1) {
        //caso alguma tecla seja pressionada, mesmo sem dar enter
        if (_kbhit()) {
            //getch para retornar tecla pressionada
            char tecla = _getch();
            //caso tecla W seja pressionada, entendo que é para subir no submenu
            if (tecla == 'W' || tecla == 'w') {
                menuCadastrar--;
                //caso contador seja menor que 0, vou para o ultimo item do submenu
                if(menuCadastrar < 0 ){
                    menuCadastrar = 4;
                }
                imprimeMenuCadastrar(menuCadastrar);
            }
            //caso tecla S seja pressionada, incrementa contador que identifica posição do submenu
            else if(tecla == 'S' || tecla == 's'){
                menuCadastrar++;
                //caso contador ultrapasse limite de 4, reseta
                if(menuCadastrar > 4){
                    menuCadastrar = 0;
                }
                imprimeMenuCadastrar(menuCadastrar);
            }
            //caso aperte enter, selecionando o item atual
            else if(tecla == 13){
                //variaveis utilizadas nas operações de cadastro
                char nome[255];
                int RG;
                int idade;
                char entrada[255];
                //caso cadastro paciente novo
                if(menuCadastrar == 0){
                    system("cls");
                    printf("Nome do Paciente: ");
                    scanf("%s", &nome);
                    printf("\nRG: ");
                    scanf("%d", &RG);
                    printf("\nIdade: ");
                    scanf("%d", &idade);
                    printf("\nEntrada: ");
                    scanf("%s", &entrada);
                    inserir_paciente(l, nome, RG, idade, entrada);
                    printf("------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
                //caso buscar paciente
                else if(menuCadastrar == 1){
                    system("cls");
                    printf("Digite o RG do Paciente que deseja consultar: ");
                    scanf("%d", &RG);
                    Paciente* paciente_procurado = buscar_paciente(l, RG);
                    if(paciente_procurado == NULL){
                        printf("\nPaciente com RG %d nao foi encontrado.\n", RG);
                    }
                    printf("------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
                //caso mostrar lista completa
                else if(menuCadastrar == 2){
                    imprimir_pacientes(l);
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
                //caso atualizar paciente
                else if(menuCadastrar == 3){
                    system("cls");
                    printf("Digite o RG do Paciente que deseja atualizar: ");
                    scanf("%d", &RG);
                    Paciente* paciente_procurado = buscar_paciente(l, RG);
                    if(paciente_procurado != NULL){
                        printf("Novo nome: ");
                        scanf("%s", &nome);
                        printf("\nNova idade: ");
                        scanf("%d", &idade);
                        printf("\nNova entrada: ");
                        scanf("%s", &entrada);
                        atualizar_paciente(l, RG, nome, idade, entrada);
                    }
                    else{
                        printf("\nPaciente com RG %d nao foi encontrado.\n", RG);
                    }
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
                //caso remover paciente
                else if(menuCadastrar == 4){
                    system("cls");
                    printf("Digite o RG do Paciente que deseja remover: ");
                    scanf("%d", &RG);
                    Paciente* paciente_procurado = buscar_paciente(l, RG);
                    if(paciente_procurado != NULL){
                        remover_paciente(l, RG);
                        printf("\nPaciente removido com SUCESSO!\n", RG);
                    }
                    else{
                        printf("\nPaciente com RG %d nao foi encontrado.\n", RG);
                    }
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
            }
            //caso usuário aperte esc ou backspace
            else if(tecla == 8 || tecla == 27){
                //reseta tanto o sub menu quanto o menuMain, e sai do loop
                menuCadastrar = 0;
                menuMain = 0;
                break;
            }
        }
    }
    imprimeMenuMain(menuMain);
    return 0;

}

int atendimento(Lista *l, Fila *f){
    imprimeMenuAtendimento(menuAtendimento);
    while (1) {
        //caso alguma tecla seja pressionada, mesmo sem dar enter
        if (_kbhit()) {
            //getch para retornar tecla pressionada
            char tecla = _getch();
            //caso tecla W seja pressionada, entendo que é para subir no submenu
            if (tecla == 'W' || tecla == 'w') {
                menuAtendimento--;
                //caso contador seja menor que 0, vou para o ultimo item do submenu
                if(menuAtendimento < 0 ){
                    menuAtendimento = 2;
                }
                imprimeMenuAtendimento(menuAtendimento);
            }
            //caso tecla S seja pressionada, incrementa contador que identifica posição do submenu
            else if(tecla == 'S' || tecla == 's'){
                menuAtendimento++;
                //caso contador ultrapasse limite de 4, reseta
                if(menuAtendimento > 2){
                    menuAtendimento = 0;
                }
                imprimeMenuAtendimento(menuAtendimento);
            }
            //caso aperte enter, selecionando o item atual
            else if(tecla == 13){
                //variaveis utilizadas nas operações de cadastro
                char nome[255];
                int RG;
                int idade;
                char entrada[255];
                if(menuAtendimento == 0){
                    system("cls");
                    printf("Digite o RG do paciente que voce deseja enfileirar: ");
                    scanf("%d", &RG);
                    Paciente* paciente_procurado = buscar_paciente(l, RG);
                    if(paciente_procurado != NULL){
                        enqueue(f, paciente_procurado->nome, paciente_procurado->RG, paciente_procurado->idade, paciente_procurado->entrada);
                    }else{
                        printf("\nPaciente com RG %d nao foi encontrado.\n", RG);
                    }
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }else if(menuAtendimento == 1){
                    system("cls");
                    dequeue(f);
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }else if(menuAtendimento == 2){
                    system("cls");
                    mostra_fila(f);
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
            }
            //caso usuário aperte esc ou backspace
            else if(tecla == 8 || tecla == 27){
                //reseta tanto o sub menu quanto o menuMain, e sai do loop
                menuAtendimento = 0;
                menuMain = 0;
                break;
            }
        }
    }
    imprimeMenuMain(menuMain);
    return 0;
}

//função pesquisa
int pesquisa(ABB *a, Lista *l){
    imprimeMenuPesquisa(menuPesquisa);
    while (1) {
        //caso alguma tecla seja pressionada, mesmo sem dar enter
        if (_kbhit()) {
            //getch para retornar tecla pressionada
            char tecla = _getch();
            //caso tecla W seja pressionada, entendo que é para subir no submenu
            if (tecla == 'W' || tecla == 'w') {
                menuPesquisa--;
                //caso contador seja menor que 0, vou para o ultimo item do submenu
                if(menuPesquisa < 0 ){
                    menuPesquisa = 3;
                }
                imprimeMenuPesquisa(menuPesquisa);
            }
            //caso tecla S seja pressionada, incrementa contador que identifica posição do submenu
            else if(tecla == 'S' || tecla == 's'){
                menuPesquisa++;
                //caso contador ultrapasse limite de 4, reseta
                if(menuPesquisa > 3){
                    menuPesquisa = 0;
                }
                imprimeMenuPesquisa(menuPesquisa);
            }
            //caso aperte enter, selecionando o item atual
            else if(tecla == 13){
                //reseta arvore para evitar bug de duplicatas
                resetar_arvore(a);
                //registros ordenados por ano de registro
                if(menuPesquisa == 0){
                    //insere pacientes já cadastrados na arvore
                    inserir_pacientes_na_arvore(a, l);
                    exibir_ordenado_por_ano(a->raiz);
                }
                //registros ordenados por mes de registro
                else if(menuPesquisa == 1){
                    //insere pacientes já cadastrados na arvore
                    inserir_pacientes_na_arvore(a, l);
                    exibir_ordenado_por_mes(a->raiz);
                }
                //registros ordenados por dia de registro
                else if(menuPesquisa == 2){
                    //insere pacientes já cadastrados na arvore
                    inserir_pacientes_na_arvore(a, l);
                    exibir_ordenado_por_dia(a->raiz);
                }
                //registros ordenados por idade de registro
                else if(menuPesquisa == 3){
                    //insere pacientes já cadastrados na arvore
                    inserir_pacientes_na_arvore(a, l);
                    exibir_ordenado_por_idade(a->raiz);
                }
            }
            //caso usuário aperte esc ou backspace
            else if(tecla == 8 || tecla == 27){
                //reseta tanto o sub menu quanto o menuMain, e sai do loop
                menuPesquisa = 0;
                menuMain = 0;
                break;
            }
        }
    }
    imprimeMenuMain(menuMain);
    return 0;
}

//função carregarSalvar
int carregarSalvar(Lista *l){
    imprimeMenuCarregarSalvar(menuCarregarSalvar);
    while (1) {
        //caso alguma tecla seja pressionada, mesmo sem dar enter
        if (_kbhit()) {
            //getch para retornar tecla pressionada
            char tecla = _getch();
            //caso tecla W seja pressionada, entendo que é para subir no submenu
            if (tecla == 'W' || tecla == 'w') {
                menuCarregarSalvar--;
                //caso contador seja menor que 0, vou para o ultimo item do submenu
                if(menuCarregarSalvar < 0 ){
                    menuCarregarSalvar = 1;
                }
                imprimeMenuCarregarSalvar(menuCarregarSalvar);
            }
            //caso tecla S seja pressionada, incrementa contador que identifica posição do submenu
            else if(tecla == 'S' || tecla == 's'){
                menuCarregarSalvar++;
                //caso contador ultrapasse limite de 4, reseta
                if(menuCarregarSalvar > 1){
                    menuCarregarSalvar = 0;
                }
                imprimeMenuCarregarSalvar(menuCarregarSalvar);
            }
            //caso aperte enter, selecionando o item atual
            else if(tecla == 13){
                // Ler um arquivo com os dados dos pacientes e carregar a lista
                if(menuCarregarSalvar == 0){
                    system("cls");
                    printf("Dados a seguir foram encontrados no arquivo, e adicionados a lista de pacientes atual:\n\n");
                    lerTxt(l);
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
                //Salvar um arquivo com os dados dos pacientes;
                else if(menuCarregarSalvar == 1){
                    system("cls");
                    cadastrarTxt(l);
                    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
                }
            }
            //caso usuário aperte esc ou backspace
            else if(tecla == 8 || tecla == 27){
                //reseta tanto o sub menu quanto o menuMain, e sai do loop
                menuCarregarSalvar = 0;
                menuMain = 0;
                break;
            }
        }
    }
    imprimeMenuMain(menuMain);
    return 0;
}

int main() {
    //inicializa lista de pacientes
    Lista *l = inicializa_lista();
    Fila *f = cria_queue();
    ABB *a = inicializar_arvore();
    imprimeMenuMain(menuMain);
    //para que a main funcione como um void loop()
    while (1) {
        //caso alguma tecla seja pressionada, mesmo sem dar enter
        if (_kbhit()) {
            //getch para retornar tecla pressionada
            char tecla = _getch();
            //caso tecla W seja pressionada, entendo que é para subir no menu
            if (tecla == 'W' || tecla == 'w') {
                menuMain--;
                //caso contador seja menor que 0, vou para o ultimo item do menu
                if(menuMain < 0 ){
                    menuMain = 4;
                }
                imprimeMenuMain(menuMain);
            }
            //caso tecla S seja pressionada, entendo que é para descer no menu
            else if (tecla == 'S' || tecla == 's') {
                menuMain++;
                //caso contador seja maior que 4, vou para o primeiro item do menu
                if(menuMain > 4 ){
                    menuMain = 0;
                }
                imprimeMenuMain(menuMain);
            }
            //caso tecla Enter seja pressionada, 13 pois o valor que a tecla enter gera é 13 (ASC2)
            else if (tecla == 13) {         // ASCII value of Enter key is 13
                if(menuMain == 0){
                    cadastrar(l);
                }else if(menuMain == 1){
                    atendimento(l, f);
                }else if(menuMain == 2){
                    pesquisa(a, l);
                }else if(menuMain == 3){
                    carregarSalvar(l);
                }else if(menuMain == 4){
                    sobre();
                }
            }
            //caso teclas BACKSPACE ou ESC sejam pressionadas, calores 8 e 27 respectivamente
            else if(tecla == 8 || tecla == 27){
                //volto para menu
                imprimeMenuMain(menuMain);
            }
        }
    }
    return 0;
}
