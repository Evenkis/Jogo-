#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105

typedef struct
{
    int linhaY, colunaX;
} posicao_t;

posicao_t le_mapa(char mapa[][COLUNAS])
{
    char nome_arq[TAM];
    printf("informe o arquivo mapa q deseja ler:");
    fgets(nome_arq,TAM,stdin);                      ///recebe a matriz para prencher
    nome_arq[strlen(nome_arq) - 1] = '\0';          ///essa funcao le o nome do arquivo, coloca na matriz recebida o que leu no
    ///arquivo
    posicao_t nave;                                 ///detecta e retorna a posi��o da nave em uma struct
    FILE *arq=NULL;
    arq = fopen(nome_arq,"r");

    for(int i = 0; i<LINHAS; i++)
        for(int j = 0; j<COLUNAS; j++)
        {
            mapa[i][j] = fgetc(arq);
            if (mapa[i][j] == '@')
            {
                nave.linhaY = i;
                nave.colunaX = j;
            }
        }

    fclose(arq);
    return nave;
}

void imprime_tela(char mapa[][COLUNAS],int lim)
{
    char tela[LINHAS][COLUNAS_TELA];
    int i;
    for(i = 0; i<LINHAS; i++)
    {
            for(int j=lim; j <  (COLUNAS_TELA+lim)   ; j++)
            {
                if((COLUNAS_TELA+j)>COLUNAS-1)
                    j = (COLUNAS_TELA + j) % COLUNAS;
                printf("%c",mapa[i][j]);
            }
        printf("\n");
    }

}


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
