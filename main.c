#include "mapa.h"
#include "mover.h"
#ifndef _DEFINES_
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#endif

#define INIMIGO_MAX 15

int main()
{
    posica_t pos;
    posicao_t posi;
    int limite = 0;
    int vel = 1;
    int i=0;
    int morreu = 0;
    int n_inimigos = 0;
    int y_nave;
    int x_nave;
    char mapa[LINHAS][COLUNAS];
    char tecla;

    // Limpa a tela
    system("cls");

    posicao_t inimigos[INIMIGO_MAX];    /// inimigos ficam na posicao

    posi = le_mapa(mapa, inimigos, &n_inimigos);  /// Passa a variavel do mapa, um vetor com tipo struct para botar a posicao dos inimigos
    pos.colunaX = posi.colunaX;//nave               /// e um ponteiro para a funcao me deizer quantos inimigos tem
    pos.linhaY = posi.linhaY;

    do
    {
        gotoxy(0,1); /// so para tirar um bugzinho esse gotoxy

        // Leitura do teclado
        if(kbhit())
        {
            tecla = getch();
            le_movimento(tecla, &(pos), &vel);
        }
        gotoxy(0,0);

        ///coloquei isso para tentar entender o bug q da quanto passa por um certo ponto (o q tem a bandeira)
        printf("linha = %d , coluna = %d , limite = %d ",pos.linhaY,pos.colunaX,limite);


        pos.colunaX += vel;
        if(pos.colunaX >= COLUNAS )
        {
            pos.colunaX = pos.colunaX - COLUNAS; //vou dizer q essas linhas n�o parecem fazer diferen�a alguma,mas
                                                 //eu sinto q elas s�o necessarias
        }
                            //se vc for tentar arrumar o bug q faz o mapa dar aquela voltada eu ja te adianto q
                            // mudar algumas coisas nas linhas 61-63 n�o � o caminho, eu tentei de tudo
                            //deve ser alguma coisa relacionada com o limite
        limite += vel;

        if (limite >= COLUNAS ) //para arrumar o limite se der varias voltas
        {
            limite = limite - COLUNAS;
        }

        x_nave = pos.colunaX;
        y_nave = pos.linhaY;

        if( i%3 == 0) /// a cada 3 intera��es, isso ser� verdadeiro e os inimigos v�o se mover(+ou- 180 ms)
            move_inimigos(mapa, inimigos, n_inimigos, y_nave, x_nave);


        detecta_colisao(mapa, pos, vel, &morreu);
        /// passa o mapa, a struct com onde ele esta, a velocidade tem q ser usada para ver se
        /// na proxima vai bater e um ponteiro para morreu


        if(morreu == 0) //uma optimizada de leve
            detecta_colisao_com_inimigo(mapa,pos,vel,&morreu);

        gera_nave(mapa,pos); //adicionei isso para ficar mais alto nivel

        limpa_rastro(tecla, pos, vel, mapa);

        // Imprime a tela
        imprime_tela(mapa, limite);
        i++;
    }
    while(!morreu);

    printf("MORREU MORREU");
    return 0;
}
