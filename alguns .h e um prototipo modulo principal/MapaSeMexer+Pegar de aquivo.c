#include "funcs_ParaMapa.h"
#include "funcs_ParaMov.h"
#include <windows.h>
#include <conio.h>
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105


int main()
{
    posicao_t pos;
    int x_nave,y_nave,limite=0,i=0;
    char mapa[LINHAS][COLUNAS];
    char c;

    pos = le_mapa(mapa);    ///usei o mapa e a função q fizemos na aula pratica aqui
    x_nave= pos.linha;
    y_nave=pos.coluna;

    do{
    if(kbhit())
    {
        c = getchar(); //não ta funcionando mt bem essa parte
        le_movimento(c,&x_nave,&y_nave,&limite);
    }

    mapa[y_nave-1][x_nave] = '@';
    for(int i=0; i<3; i++)
        mapa[y_nave][x_nave+i] = '@';
    x_nave++;
    limite++;
    imprime_tela(mapa,limite);      //ja fiz esse prog com modulos.
    mapa[y_nave-1][x_nave-1] = ' '; ///proximos passos(não necessariamente nessa ordem): colocar if q aceita passar X tempo ou se apertar alguma coisa
    mapa[y_nave][x_nave-1] = ' ';   ///Colocar ifs para detectar colisão
                                    /// ifs para colocoar espaços em branco se a nave subiu ou desceu como fiz na linhas 35-36
    gotoxy(0,0);                    /// Fazer o mapa recomeçar se chegar no final
    i++;                            /// adicionar a velocidade da nave (tipo o q fiz na linha 32-33),
                                    ///mas vai ter q ser na func le_movimento provavelmente
    }while(x_nave<50);              ///dps disso tudo acho q podemos a trabalhar com tiros e inimigos
    //esse while só para ver funcionar um pouco





    return 0;
}
