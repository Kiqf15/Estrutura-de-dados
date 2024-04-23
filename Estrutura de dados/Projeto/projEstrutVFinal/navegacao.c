#include <conio.h>
#include <stdio.h>
//funções que imprimem os menus e submenus

//função que imprime a seção sobre
void sobre(){
    system("cls");
    printf("------------------------SOBRE------------------------\nALUNOS:\nMatheus Miranda Vieira , RA: 22220017-2\nKaique da Silva Fernandes , RA: 22221011-4\nNicolas Costa Coppola de Moraes , RA: 22122099-9\nCICLO: Quarto Ciclo\nCURSO: Ciencia da Computacao\nDISCIPLINA: Estrutura de Dados\nDATA: 23/10/2023\n-----------------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: W, S, ESC, BACKSPACE. ");
}

//função que recebe o contador do menuMain, e atualiza o menu de forma correspondente
int imprimeMenuMain(int c){
    //limpa tela/terminal
    system("cls");
    if(c == 0){
        printf("Cadastrar <-\nAtendimento\nPesquisa\nCarregar / Salvar\nSobre");
    }else if(c == 1){
        printf("Cadastrar\nAtendimento <-\nPesquisa\nCarregar / Salvar\nSobre");
    }else if(c == 2){
        printf("Cadastrar\nAtendimento\nPesquisa <-\nCarregar / Salvar\nSobre");
    }else if(c == 3){
        printf("Cadastrar\nAtendimento\nPesquisa\nCarregar / Salvar <-\nSobre");
    }else if(c == 4){
        printf("Cadastrar\nAtendimento\nPesquisa\nCarregar / Salvar\nSobre <-");
    }
    printf("\n------------------------------------------\nNavegacao: \nTecla 'W' -> Item acima | Tecla 'S' -> Item abaixo | Tecla 'Enter' -> Seleciona item atual");
    printf("\n");
    return 0;
}

//função que recebe o contador do menuCadastrar, e atualiza o submenu de forma correspondente
int imprimeMenuCadastrar(int c){
    system("cls");
    if(c == 0){
        printf("Cadastrar novo paciente <-\nConsultar paciente cadastrado\nMostrar lista completa\nAtualizar dados de paciente\nRemover paciente");
    }else if(c == 1){
        printf("Cadastrar novo paciente\nConsultar paciente cadastrado <-\nMostrar lista completa\nAtualizar dados de paciente\nRemover paciente");
    }else if(c == 2){
        printf("Cadastrar novo paciente\nConsultar paciente cadastrado\nMostrar lista completa <-\nAtualizar dados de paciente\nRemover paciente");
    }else if(c == 3){
        printf("Cadastrar novo paciente\nConsultar paciente cadastrado\nMostrar lista completa\nAtualizar dados de paciente <-\nRemover paciente");
    }else if(c == 4){
        printf("Cadastrar novo paciente\nConsultar paciente cadastrado\nMostrar lista completa\nAtualizar dados de paciente\nRemover paciente <-");
    }
    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
    printf("\n");
    return 0;
}

int imprimeMenuAtendimento(int c){
    system("cls");
    if(c == 0){
        printf("Enfileirar Paciente <-\nDesenfileirar Paciente\nMostrar Fila");
    }else if(c == 1){
        printf("Enfileirar Paciente\nDesenfileirar Paciente <-\nMostrar Fila");
    }else if(c == 2){
        printf("Enfileirar Paciente\nDesenfileirar Paciente\nMostrar Fila <-");
    }
    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
    printf("\n");
    return 0;
}

int imprimeMenuPesquisa(int c){
    system("cls");
    if(c == 0){
        printf("Mostrar registros ordenados por ANO de registro <-\nMostrar registros ordenados por MES de registro\nMostrar registros ordenados por DIA de registro\nMostrar registros ordenados por IDADE do paciente");
    }else if(c == 1){
        printf("Mostrar registros ordenados por ANO de registro\nMostrar registros ordenados por MES de registro <-\nMostrar registros ordenados por DIA de registro\nMostrar registros ordenados por IDADE do paciente");
    }else if(c == 2){
        printf("Mostrar registros ordenados por ANO de registro\nMostrar registros ordenados por MES de registro\nMostrar registros ordenados por DIA de registro <-\nMostrar registros ordenados por IDADE do paciente");
    }else if(c == 3){
        printf("Mostrar registros ordenados por ANO de registro\nMostrar registros ordenados por MES de registro\nMostrar registros ordenados por DIA de registro\nMostrar registros ordenados por IDADE do paciente <-");
    }
    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
    printf("\n");
    return 0;
}

int imprimeMenuCarregarSalvar(int c){
    system("cls");
    if(c == 0){
        printf("Ler Arquivo com dados dos pacientes & carregar lista <-\nSalvar Arquivo com dados dos pacientes");
    }else if(c == 1){
        printf("Ler Arquivo com dados dos pacientes & carregar lista\nSalvar Arquivo com dados dos pacientes <-");
    }
    printf("\n------------------------------------------\nPara retornar ao menu inicial, pressione uma das seguintes teclas: ESC, BACKSPACE.");
    printf("\n");
    return 0;
}