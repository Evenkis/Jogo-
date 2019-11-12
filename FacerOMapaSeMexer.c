#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define L 12
#define C 73
#define LIMITE 30

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void printa(char matriz[][C])
{
    for(int l=0; l<L; l++)
    {
        for (int c=0; c<C; c++)
        {
            printf("%c",matriz[l][c]);   //printa matriz (não tem mais uso eu acho)
        }
        printf("\n");
    }
}

void printa_mapa(int lim,char mapa[][C]) //passa o lim que varia conforme o jogador aperta "D"
{
    for(int l=0; l<L; l++)
    {
        for (int c=0+lim; c<LIMITE+lim; c++)   //o comeco e o final são ambos incrementados em lim, então a matriz não muda de tamanho
        {
            printf("%c",mapa[l][c]);
        }
        printf("\n");
    }
}

void le_movimento(char c,int *px,int *py,int *lim) //fiz uma função para ler tb
{
    if(c == 'w')            // se c for w vai ter o y-- e impressão da nova matriz
        *py=(*py)-1;                // tem q ser -- pq y é as linhas e com W quero q a nave suba, mas da para melhorar isso
    if(c == 's')
        *py=(*py)+1;
    if(c == 'd')
        {
        *px=(*px)+1;
        *lim = (*lim) + 1; //aqui é a parte mais importante.
        }
    if(c == 'a')
        *px=(*px)-1; //já que agora o mapa anda e ainda não fizemos o jogo nas duas direções isso pode ser tirado.
}



int main()
{
    char mapa[L][C] = {0};
    int limite; //é o q vai mexer o mapa para frente
    int y_nave=6; //é o q vai mexer a nave para cima e para baixo
    int x_nave = 0;
    int apertou = 1;
    char c;
    do
    {
        if( kbhit())                    //se algo for lido kbhit retorna 1
        {
            c = getch();
            le_movimento(c,&x_nave,&y_nave,&limite);
            apertou = 1;
        }

        if(apertou)                      //só para não ficar gerando a matriz mil vezzes por segundo se o cara não apertou nada
            for(int l=0; l<L; l++)
            {
                for (int c=0; c<C; c++)
                {
                    if (l==0 || l==L-1)
                        mapa[l][c] = '#';
                    else
                        mapa[l][c] = ' ';
                    if (c%3==0 && l<3)
                        mapa[l][c] = '#';
                    //gera a matriz aqui
                }
            }
        if(apertou)
        {
            mapa[y_nave-1][x_nave] = '@';
            for(int i=0; i<3; i++)
                mapa[y_nave][x_nave+i] = '@';  // a parte de fazer a nave comprida.
            gotoxy(0,0);
            printa_mapa(limite,mapa);
        }
    apertou = 0;
    }
    while(y_nave != 1 );

    return 0;

}
