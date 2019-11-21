#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>

#ifndef _DEFINES_
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#define TELA_MAX 3710+1
#endif


typedef struct {
    int linhaY, colunaX;
} posicao_t;

posicao_t le_mapa(char mapa[][COLUNAS],posicao_t inimigos[],int *ini) {
    char nome_arq[TAM];
    int i, j;

    printf("informe o arquivo mapa q deseja ler:");
    fgets(nome_arq,TAM,stdin);                      ///recebe a matriz para prencher
    nome_arq[strlen(nome_arq) - 1] = '\0';          ///essa funcao le o nome do arquivo, coloca na matriz recebida o que leu no arquivo
    posicao_t nave;                                 ///detecta e retorna a posicao da nave em uma struct
    FILE *arq=NULL;
    arq = fopen(nome_arq,"r");

    for(i = 0; i<LINHAS; i++)
        for(j = 0; j<COLUNAS; j++)
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

void imprime_tela(char mapa[][COLUNAS],int lim) {
//    char tela[LINHAS][COLUNAS_TELA];
    int i, j;
    char tela[TELA_MAX] = "";

    for(i = 0; i<LINHAS; i++)
    {
        for(j=lim; j < (COLUNAS_TELA+lim); j++)
        {
            strncat(tela, &mapa[i][j], 1);
            // tela[(i+1)*j] = mapa[i][j];
            
            // if((COLUNAS_TELA+j)>COLUNAS-1)
            //     j = (COLUNAS_TELA + j) % COLUNAS;
            // printf("%c",mapa[i][j]);
        }
        strcat(tela, "\n");
        // tela[(i+1)*j + 1] = '\n';
        // tela[(i+1)*j + 2] = '\0';
        // printf("%s", tela);

        // printf("\n");
    }
    strcat(tela, "\0");
    // tela[TELA_MAX - 1] = '\0';

    printf("%s", tela);

    Sleep(100);
}


void move_inimigos(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int y_nave,int x_nave) {
    int i=0,n_aleatorio;
    srand(time(NULL));

    for(i = 0; i<n_inimigos; i++)
    {
        n_aleatorio = (rand()%(6)); ///gerar o numero aleatorio
        if(n_aleatorio < 3 && (y_nave != inimigos[i].linhaY) && ( (fabs(x_nave - inimigos[i].colunaX)) < 50))
        {                       ///(n_aleatorio � para probabilidade), se n�o tiver na mesma linha e estiver proximo
            if((y_nave - inimigos[i].linhaY)<0)
            {                   /// se estiver a baixo, sobe
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                inimigos[i].linhaY = inimigos[i].linhaY - 1;
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
            }
            else
            { ///se n�o, desce
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                inimigos[i].linhaY = inimigos[i].linhaY + 1;
                mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
            }
        }
        else
        { ///se n�o passou em algum daqueles requisitos, pode com chance de 50% subir ou descer
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
        if(  (fabs(x_nave - inimigos[i].colunaX))< 120) ///s� anda para frente se estiver perto de 120 colunas
        {
            (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = ' '; ///faz todos os ininmigos nadarem para frente
            inimigos[i].colunaX = inimigos[i].colunaX - 1;
            (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = 'X';
        }
    }
}

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

