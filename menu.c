//PROTOTIPO MENU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

#define VERSION "0.0.1\0"
#define TAM 50
#define LIN 35
#define COL 415+1
#define COL_TELA 105
#define NEW_GAME_TEXT "Novo Jogo   \0"
#define CONTINUE_TEXT "Continuar   \0"
#define EXIT_TEXT "Sair   \0"

// Funcao gotoxy (mover cursor)
void gotoxy(int x, int y) {
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Printa menu
void printMenu(int option) {
    gotoxy(30, 14);
    char menuText[TAM] = "-> ";
    if(option == 0){
        strcat(menuText, NEW_GAME_TEXT);
    } else {
        strcpy(menuText, NEW_GAME_TEXT);
    }
    printf(menuText);

    gotoxy(30, 17);
    strcpy(menuText, "-> ");
    if(option == 1){
        strcat(menuText, CONTINUE_TEXT);
    } else {
        strcpy(menuText, CONTINUE_TEXT);
    }
    printf(menuText);

    gotoxy(30, 20);
    strcpy(menuText, "-> ");
    if(option == 2){
        strcat(menuText, EXIT_TEXT);
    } else {
        strcpy(menuText, EXIT_TEXT);
    }
    printf(menuText);

    gotoxy(COL_TELA, LIN);
    printf("F");

    return;
}


// Selecao de opcoes
void selecao(int* psel) {
    int flag;
    char c;

    // Deteccao teclas
    if(kbhit()){
        c = getch();
        flag = 0;
    }
    
    if(c == 'w' && !flag && *psel > 0){
        *psel = *psel - 1;  // *psel--; NAO FUNCIONA!
        flag = 1;
    }
    if(c == 's' && !flag && *psel < 2){
        *psel = *psel + 1;  // *psel++; NAO FUNCIONA!
        flag = 1;
    }

    printMenu(*psel);

    return;
}


int main() {
    int sel = 1;
    int* psel = &sel;

    //Limpa o CMD
    system("cls");
    printf(VERSION);

    //Executa a primeira impressao
    printMenu(0);

    while(1){
        selecao(psel);
        Sleep(100);
    }


    return 0;
}

