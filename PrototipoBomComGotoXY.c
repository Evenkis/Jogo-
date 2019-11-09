#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

#define L 10
#define C 30

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
            printf("%c",matriz[l][c]);   //printa ela.
        }
        printf("\n");
    }
}
int main()
{
    char M[L][C];
    char c;
    int morreu=1;
    int flag = 1,apertou=1;
    int x=4;
    int y=4; //para posição do @
    int yt=5,xt=8;
    int i = 0;
    do
    {

        if( kbhit())                    //se algo for lido kbhit retorna 1
        {
            c = getch();
            //se algo for lido esse algo vai para c
            apertou = 1;
            if(c == 'w')            // se c for w vai ter o y-- e impressão da nova matriz
                y--;                // tem q ser -- pq y é as linhas e com W quero q a nave suba, mas da para melhorar isso
            if(c == 's')
                y++;
            if(c == 'd')
                x++;
            if(c == 'a')
                x--;
        }
        if(apertou)                         //só para não ficar gerando a matriz mil vezzes por segundo se o cara não apertou nada
            for(int l=0; l<L; l++)
            {
                for (int c=0; c<C; c++)
                {
                    if (l==0 || l==9)
                        M[l][c] = '#';
                    else
                        M[l][c] = ' ';
                    //gera a matriz aqui
                }
            }
        M[yt][xt] = '<';
        if ( M[y][x] == '<')
        {
            gotoxy(0,12);
            printf("\n--> MORREU <--\n");
            morreu = 0;
        }
        if(M[y][x]=='#')
        {
            gotoxy(0,12);
            printf("\n--> MORREU <--\n");       //tem um tiro q fica subindo cada vez q chega no final na matriz, não entendi como
                                                //resolver para ficar na mesma linha, mas o principal era fazer com q se batesse no tiro
                                                // ou nas paredes ele morresse
                                                // e tambem ainda é a nave q movimenta, não o mapa.

            morreu = 0;
        }
        else
        {
            M[y][x] = '@'; //a "nave"

            if (flag || apertou)
            {
                //flag é só para não fazer print toda vez
                printa(M);
                gotoxy(0,11);
                printf("Printei %d vezes ",i);
                i++;
                xt--;

//                if(xt==29 && yt!=5)
//                    yt=5;

                //apertou que vai decidir se printa ou não
            }                                            //deve ter uma maneira melhor de fazer isso
            flag = 0;
            apertou = 0;
            gotoxy(0,0);

        }
    }
    while(morreu);
    return 0;
}
