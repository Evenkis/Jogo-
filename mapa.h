#ifndef _DEFINES_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <sys/time.h>

#define LINHAS 35
#define TAM 50
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#define TELA_MAX 3710+1

#endif


typedef struct
{
    int linhaY, colunaX;
} posicao_t;

// Funcao gotoxy
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Funcao que le o mapa e detecta a nave e os inimigos
posicao_t le_mapa(char mapa[][COLUNAS], posicao_t inimigos[], int *ini, int sel)
{
    char nome_arq[TAM];
    int i, j;

    // Se 'Novo Jogo' for selecionado, le o nome do arquivo mapa
    if(sel == 0){
        // Pega o nome do arquivo do mapa a ser aberto

        system("cls");  // limpa cmd

        gotoxy(20,14);
        printf("Informe o arquivo mapa que deseja ler: ");
        fgets(nome_arq, TAM, stdin);    /// recebe o nome do arquivo
        nome_arq[strlen(nome_arq) - 1] = '\0';
    }
    // Se 'Continuar' for selecionado, le o arquivo save.txt
    else if(sel == 1){
        strcpy(nome_arq, "save.txt");
    }

    posicao_t nave; /// detecta e retorna a posicao da nave em uma struct

    // Abertura do arquivo como read-only
    FILE *arq=NULL;
    arq = fopen(nome_arq, "r");

    // Navegando no mapa
    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            // Copia o mapa para a variavel mapa
            mapa[i][j] = fgetc(arq);

            // Encontra a posicao da nave
            if (mapa[i][j] == '@')
            {
                nave.linhaY = i;
                nave.colunaX = j;
            }

            // Encontra a posicao dos inimigos
            if(mapa[i][j]== 'X')
            {
                inimigos[(*ini)].colunaX = j;
                inimigos[(*ini)].linhaY = i;
                (*ini)++;
            }
        }
    }

    // Fecha o arquivo
    fclose(arq);

    // Retorna a posicao da nave
    return nave;
}

//Imprime a tela (stringao)
void imprime_tela(char mapa[][COLUNAS],int lim)
{
    int i, j, k;
    char tela[TELA_MAX] = "";   // Cria o stringao vazio

    // Navega pelo mapa (ja inclui velocidade e limite e sla mais o que)
    for(i = 0; i < LINHAS; i++)
    {
        for(j = lim; j < (COLUNAS_TELA + lim); j++)
        {
            if( (j+COLUNAS_TELA) >= COLUNAS  )
            {
                k = (j + COLUNAS_TELA - COLUNAS ); //o q faz o mapa voltar
            }
            else
                k = j ;

            // Le 1 char do mapa e concatena no stringao
            strncat(tela, &mapa[i][k], 1);
        }
        //Adiciona o \n no final de cada linha
        strcat(tela, "\n");
    }
    // Adiciona o \0 ao final do stringao
    strcat(tela, "\0");

    // Posiciona o cursor no inicio
    gotoxy(0,1);

    // Finalmente printa o stringao na tela
    printf("%s", tela);

    // Dorme um pouquinho :D
    Sleep(60);
}

// Funcao que move os inimigos
void move_inimigos(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int y_nave,int x_nave)
{
    int i = 0;
    int n_aleatorio;
    srand(time(NULL));
        for(i = 0; i<n_inimigos; i++) ///tem q fazer os inimigos iriem mais devagar.
        {
            n_aleatorio = (rand()%(8)); /// gerar o numero aleatorio
            /// (n_aleatorio eh para probabilidade), se nao tiver na mesma linha e estiver proximo
            if(n_aleatorio < 2 && (y_nave != inimigos[i].linhaY) && ( (fabs(x_nave - inimigos[i].colunaX)) < 70))
            {
                /// se estiver a baixo, sobe
                if((y_nave - inimigos[i].linhaY)<0)
                {
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';    // deleta a posicao antiga
                    inimigos[i].linhaY = inimigos[i].linhaY - 1;            // altera a posicao
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';    // imprime na posicao nova
                }
                ///se nao, desce
                else
                {
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                    inimigos[i].linhaY = inimigos[i].linhaY + 1;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
                }
            }
            ///se nao passou em algum daqueles requisitos, tem 50% de chance de subir ou descer
            else
            {
                n_aleatorio = (rand() % 2);
                if(n_aleatorio == 1)
                {
                    if( inimigos[i].linhaY <= 1 )
                    {
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                        inimigos[i].linhaY = inimigos[i].linhaY - 1;
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
                    }
                }
                else
                {
                    if(inimigos[i].linhaY >= 34)
                    {
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                        inimigos[i].linhaY = inimigos[i].linhaY + 1;
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
                    }
                }
            }
            /// so anda para frente se estiver perto de 120 colunas
            if( (fabs(x_nave - inimigos[i].colunaX)) < 120)
            {
                /// faz todos os ininmigos andarem para frente
                (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = ' ';
                inimigos[i].colunaX = inimigos[i].colunaX - 1;
                (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = 'X';

                if(inimigos[i].colunaX == 0)// para quando chegar no come�o da matriz ver ir pro fim
                    inimigos[i].colunaX = 415;
            }
        }

}
