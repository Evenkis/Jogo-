//coisinha basica que serviu s� para aprender kbhit() mas valeu a pena
#include <stdio.h>
#include <stdlib.h>
#define L 10
#define C 10

#include <conio.h> //a biblioteca q tem o scanf que n�o para o prog

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
    int y=4; //para posi��o do @
    int yt=4,xt=8;

    do
    {

        if( kbhit())                    //se algo for lido kbhit retorna 1
        {
            c = getch();
            xt--;
                                    //se algo for lido esse algo vai para c
            apertou = 1;                    //para entrar naquele if l� em cima

            if(c == 'w')            // se c for w vai ter o y-- e impress�o da nova matriz
                y--;                // tem q ser -- pq y � as linhas e com W quero q a nave suba, mas da para melhorar isso
            if(c == 's')
                y++;
            if(c == 'd')
                x++;
            if(c == 'a')
                x--;
        }
        if(apertou)                         //s� para n�o ficar gerando a matriz mil vezzes por segundo se o cara n�o apertou nada
            for(int l=0; l<L; l++)
            {
                for (int c=0; c<C; c++)
                {
                    M[l][c] = '.';
                    //gera a matriz aqui
                }
            }
        M[yt][xt] = '<'; //tiro qualquer

        if(M[y][x] ==  '<')
            {
            printf("morreu");
            morreu = 0;
            }
        else
            M[y][x] = '@'; //a "nave"

        if (flag || apertou)
            {
            printf("\n");                        //flag � s� para n�o fazer print toda vez
            printa(M);                      //apertou que vai decidir se printa ou n�o
            }                                //deve ter uma maneira melhor de fazer isso
        flag = 0;
        apertou = 0;
    }
    while(y!=-1 && morreu);
    return 0;
}
