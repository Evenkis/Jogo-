#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <sys/time.h>
#ifndef _DEFINES_
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#define TELA_MAX 3710+1
#endif


typedef struct
{
    int linhaY, colunaX;
} posicao_t;

// Funcao gotoxy
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int ve_se_inimigo_vai_bater_parede( posicao_t inimigo,char mapa[][COLUNAS],int subiu_desceu )
{
    if(subiu_desceu == 1)
    {
        if(   (mapa[inimigo.linhaY-2][inimigo.colunaX])  == 'C')
            return 0;
        else
            return 1;
    }
    else
    {
        if ( (mapa[inimigo.linhaY+1][inimigo.colunaX]) == 'C')
            return 0;
        else
            return 1;

    }
}

// Funcao que le o mapa e detecta a nave e os inimigos
posicao_t le_mapa(char mapa[][COLUNAS],posicao_t inimigos[], int *ini)
{
    char nome_arq[TAM];
    int i, j;

    // Pega o nome do arquivo do mapa a ser aberto
    /// Vai ser alterado no futuro provavelmente...
    printf("Informe o arquivo mapa que deseja ler: ");
    fgets(nome_arq, TAM, stdin);    /// recebe o nome do arquivo
    nome_arq[strlen(nome_arq) - 1] = '\0';

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
    Sleep(80);
}


/// ---- INOP ----
// Funcao que move os inimigos
void move_inimigos(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int y_nave,int x_nave)
{
    int i = 0;
    int n_aleatorio,subiu,desceu;
    srand(time(NULL));
    for(i = 0; i<n_inimigos; i++)
    {
        subiu = 0;
        desceu = 0;
        n_aleatorio = (rand()%(8)); /// gerar o numero aleatorio
        /// (n_aleatorio eh para probabilidade), se nao tiver na mesma linha e estiver proximo
        if(n_aleatorio < 3 && (y_nave != inimigos[i].linhaY) && ( (fabs(x_nave - inimigos[i].colunaX)) < 90))
        {
            /// se estiver a baixo, sobe
            if((y_nave - inimigos[i].linhaY)<0) ///para subir
            {
                if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,1) == 1 )
                {
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' '; // deleta a posicao antiga
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
                    /// 1 para subir -1 para descer
                    inimigos[i].linhaY = inimigos[i].linhaY - 1;               // altera a posicao

                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = 'X';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = 'X';
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = 'X';

                    subiu = 1;
                }            //bota na nova


            }
            ///se nao, desce
            else
            {
                if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,-1) == 1 )
                {
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';

                    inimigos[i].linhaY = inimigos[i].linhaY + 1;

                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = 'X';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = 'X';
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = 'X';
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';

                    desceu = 1;

                }
            }
        }
        ///se nao passou em algum daqueles requisitos, tem 33% de chance de subir ou descer
        else
        {
            n_aleatorio = (rand() % 3);
            if(n_aleatorio == 1)
            {
                if( (inimigos[i].linhaY) >= 3 )
                {
                    if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,1) == 1 )
                    {
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';



                        inimigos[i].linhaY = inimigos[i].linhaY - 1;

                        mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = 'X';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = 'X';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = 'X';
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';

                        subiu = 1;
                    }
                }
            }
            else if (n_aleatorio == 2)
            {
                if(  (inimigos[i].linhaY) <= 33)
                {
                    if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,-1) == 1 )
                    {
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';

                        inimigos[i].linhaY = inimigos[i].linhaY + 1;

                        mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = 'X';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = 'X';
                        mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = 'X';
                        mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X';

                        desceu = 1;
                    }
                }
            }
        }


        /// so anda para frente se estiver perto de 120 colunas
        if( (fabs(x_nave - inimigos[i].colunaX)) < 120)
        {
            /// faz todos os ininmigos andarem para frente
            {
                mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
                mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
                (mapa[inimigos[i].linhaY-1][inimigos[i].colunaX]) = ' ';
                (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = ' ';

                inimigos[i].colunaX = inimigos[i].colunaX - 1;

                mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = 'X';
                mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = 'X';
                (mapa[inimigos[i].linhaY-1][inimigos[i].colunaX]) = 'X';
                (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = 'X';
            }


        }
        if(inimigos[i].colunaX <= 1)     // para quando chegar no come�o da matriz ver ir pro fim
            inimigos[i].colunaX = 415;
    }




}






