#include "mov.h"
#include "mover.h"
#include <windows.h>
#include <conio.h>
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105


int main()
{
    posica_t pos;
    posicao_t poss;
    int limite=0,i=0,vel=0,morreu=0;
    char mapa[LINHAS][COLUNAS];
    char c;

    poss = le_mapa(mapa);    ///usei o mapa e a função q fizemos na aula pratica aqui
    pos.colunaX = poss.colunaX;
    pos.linhaY = poss.linhaY;

    do
    {
        if(kbhit())
        {
            c = getch();
            le_movimento(c,&(pos),&vel);
        }

        pos.colunaX+=vel;
        limite+=vel;

        for(i=0; i<4; i++)
            if(mapa[pos.linhaY][pos.colunaX+1] != '@' )
               {
                   morreu = 1;
               }

        mapa[pos.linhaY-1][pos.colunaX] = '@';
        for(i=0; i<4; i++)
            mapa[pos.linhaY][pos.colunaX+i] = '@';

        limpa_rastro(c,pos,vel,mapa);
        ///proximos passos(não necessariamente nessa ordem): colocar if q aceita passar X tempo ou se apertar alguma coisa
        imprime_tela(mapa,limite);

                gotoxy(0,0);
              if(morreu)
                   printf("MORREU MORREU");                        /// Fazer o mapa recomeçar se chegar no final


    }
    while(1);                       ///dps disso tudo acho q podemos a trabalhar com tiros e inimigos
    return 0;
}
