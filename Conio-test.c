#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define L 20
#define C 80

//Funcao gotoxy (mover cursor)
void gotoxy(int x, int y) {
    COORD coord = {0, 0};
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//Gera e imprime a matriz pela primeira vez
void primeira(char M[][C]){
    int i, j;

    //Limpa o CMD
    system("cls");

    //Gera a matriz de pontos
    for(i = 0; i < L; i++){
        for(j = 0; j < C; j++){
            M[i][j] = '.';
        }
    }

    //Coloca um O no ponto de origem
    M[10][40] = 'O';

    //Printa a matriz
    for(i = 0; i < L; i++){
        for(j = 0; j < C; j++){
            gotoxy(j, i);
            printf("%c", M[i][j]);
        }
    }
}

//Funcao mover nave
void move(char M[][C], int coord[], char tecla){
    //Escreve o que existe na matriz de pontos
    //por cima da posicao anterior da nave
    gotoxy(coord[1], coord[0]);
    printf("%c", M[coord[0]][coord[1]]);
    
    //Altera as coords da nave de acordo com a tecla pressionada
    switch (tecla) {
        case 'w':
            coord[0]--;
            break;

        case 's':
            coord[0]++;
            break;

        case 'a':
            coord[1]--;
            break;

        case 'd':
            coord[1]++;
            break;
    }
    
    //Escreve a nave na nova posicao
    gotoxy(coord[1], coord[0]);
    printf("@");

}

int main() {
    char M[L][C];   //Matriz "mapa"
    char c;         //Tecla pressionada
    int coordNave[2] = {10,40}; //Coordenadas da nave
    int morreu = 0;


    printf("-Inicio-\n");

    //Executa a primeira funcao
    primeira(M);


    //Loop infinito só para testar
    do{
        //Captura a tecla pressionada
        //e executa a funcao de movimentar a nave
        if(kbhit()) {
            c = getch();
            move(M, coordNave, c);
        }

    }while(morreu == 0);

    return 0;
}