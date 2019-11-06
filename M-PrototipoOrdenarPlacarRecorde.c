#include <stdlib.h>
#include <stdio.h>
#define TAM 3

typedef struct placar
{
    int pontos;
    char nome[4];

} placar_t;

void ordenar(placar_t pessoas[])
{
    placar_t temp;
    int flag=1;
    do
    {
        flag=1;
        for(int i = 0; i<TAM-1; i++)
            {
                if(pessoas[i].pontos > pessoas[i+1].pontos)
                {
                    flag=0;
                    temp = pessoas[i];
                    pessoas[i] = pessoas[i+1];
                    pessoas[i+1] = temp;
                }
            }
    }while(!flag);

}




int main()
{
    placar_t pessoas[TAM] = {0,"c",0,"a",0,"b"};

    pessoas[0].pontos = 00;     //claro q o nome seria feito a partir de um fgets e a pontuação viria do joog
                                //, mas o ordenamento por bolha ja está feito
    pessoas[1].pontos = 50;

    pessoas[2].pontos = 110;

    ordenar(pessoas);

    for(int i = TAM-1; i>=0; i--)           //O ordenamento deixa do menor pro maior, então printf ao contrario
        printf("%s -- %d\n",pessoas[i].nome,pessoas[i].pontos);
    return 0;
}
