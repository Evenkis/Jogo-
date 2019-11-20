#include "mov.h"
#include "mover.h"
#include <windows.h>
#include <conio.h>
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#define INIMIGO_MAX 15

int main()
{
    posica_t pos;
    posicao_t posi;
    int limite=0,i=0,vel=0,morreu=0,n_inimigos=0;
    char mapa[LINHAS][COLUNAS];
    char c;
    posicao_t inimigos[INIMIGO_MAX];

    posi = le_mapa(mapa,inimigos,&n_inimigos); ///passo o mapa para ler, um vetor com tipo struct para botar a posição dos inimiog
    pos.colunaX = posi.colunaX;                ///e um ponteiro para a função me deizer quantos inimigos tem
    pos.linhaY = posi.linhaY;

    do
    {
        gotoxy(0,0); ///só para tirar um bugzinho esse gotoxy
        morreu = 0;
        if(kbhit())
        {
            c = getch();
            le_movimento(c,&(pos),&vel);
        }

        pos.colunaX+=vel;
        limite+=vel;

        for(i = 0;i<n_inimigos;i++)
        {
            (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = ' '; ///faz todos os ininmigos nadarem para frente
            inimigos[i].colunaX = inimigos[i].colunaX - 1;
            (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) = 'X';
        }

        detecta_colisao(mapa,pos,vel,&morreu); ///passa o mapa, a struct com onde ele esta, a velocidade tem q ser usada para ver se
                                                /// na proxima vai bater e um ponteiro para morreu
            mapa[pos.linhaY-1][pos.colunaX] = '@';  ///faz a nave ficar grande
            for(i=0; i<4; i++)
            {
                mapa[pos.linhaY][pos.colunaX+i] = '@';
            }
            limpa_rastro(c,pos,vel,mapa);       ///só para ficar o rastro, bem simples
                                                ///proximos passos(não necessariamente nessa ordem):

            imprime_tela(mapa,limite);

            gotoxy(0,0);

                                                /// Fazer o mapa recomeçar se chegar no final
    }
    while(morreu != -1);
    printf("MORREU MORREU");                      ///dps disso tudo acho q podemos a trabalhar com tiros e inimigos
    return 0;
}
