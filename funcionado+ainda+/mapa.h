#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105

typedef struct
{
    int linhaY, colunaX;
} posicao_t;

posicao_t le_mapa(char mapa[][COLUNAS],posicao_t inimigos[],int *ini)
{
    char nome_arq[TAM];
    printf("informe o arquivo mapa q deseja ler:");
    fgets(nome_arq,TAM,stdin);                      ///recebe a matriz para prencher
    nome_arq[strlen(nome_arq) - 1] = '\0';          ///essa funcao le o nome do arquivo, coloca na matriz recebida o que leu no
    ///arquivo
    posicao_t nave;                                 ///detecta e retorna a posição da nave em uma struct
    FILE *arq=NULL;
    arq = fopen(nome_arq,"r");
    int i;

    for(i = 0; i<LINHAS; i++)
        for(int j = 0; j<COLUNAS; j++)
        {
            mapa[i][j] = fgetc(arq);
            if (mapa[i][j] == '@')
            {
                nave.linhaY = i;
                nave.colunaX = j;
            }
            if(mapa[i][j]== 'X')
            {
                inimigos[(*ini)].colunaX = j;
                inimigos[(*ini)].linhaY = i;
                (*ini)++;
            }
        }

    fclose(arq);
    return nave;
}

void imprime_tela(char mapa[][COLUNAS],int lim)
{
//    char tela[LINHAS][COLUNAS_TELA];
    int i;
    for(i = 0; i<LINHAS; i++)
    {
        for(int j=lim; j <  (COLUNAS_TELA+lim)   ; j++)
        {
            if((COLUNAS_TELA+j)>COLUNAS-1)
                j = (COLUNAS_TELA + j) % COLUNAS; ///ainda não consegui fazer o mapa fechar
            printf("%c",mapa[i][j]);
        }
        printf("\n");
    }

}


void move_inimigos(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int y_nave,int x_nave)
{
    int i=0,n_aleatorio;
    srand(time(NULL));

    for(i = 0; i<n_inimigos; i++)
    {
        n_aleatorio = (rand()%(6)); ///gerar o numero aleatorio
        if(n_aleatorio < 3 && (y_nave != inimigos[i].linhaY) && ( (fabs(x_nave - inimigos[i].colunaX)) < 50))
        {                       ///(n_aleatorio é para probabilidade), se não tiver na mesma linha e estiver proximo
            if((y_nave - inimigos[i].linhaY)<0)
            {                   /// se estiver a baixo, sobe
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                inimigos[i].linhaY = inimigos[i].linhaY - 1;
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
            }
            else
            { ///se não, desce
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                inimigos[i].linhaY = inimigos[i].linhaY + 1;
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
            }
        }
        else
        { ///se não passou em algum daqueles requisitos, pode com chance de 50% subir ou descer
            n_aleatorio = (rand()%(2));
            if( n_aleatorio == 1 )
            {
                if( inimigos[i].linhaY != 0 )
                {
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                    inimigos[i].linhaY = inimigos[i].linhaY - 1;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
                }
            }
            else
            {
                if( inimigos[i].linhaY != 35 )
                {
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                    inimigos[i].linhaY = inimigos[i].linhaY + 1;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
                }
            }

        }
        if(  (fabs(x_nave - inimigos[i].colunaX))< 120) ///só anda para frente se estiver perto de 120 colunas
        {
            (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = ' '; ///faz todos os ininmigos nadarem para frente
            inimigos[i].colunaX = inimigos[i].colunaX - 1;
            (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = 'X';
        }
    }
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

