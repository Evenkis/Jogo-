#include "mapa.h"
#include "mover.h"

#ifndef _DEFINES_
#define LINHAS 35
#define TAM 20
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#endif

#define INIMIGO_MAX 15

int main() {
    posica_t pos;
    posicao_t posi;
    int limite = 0;
    int i = 0;
    int vel = 0;
    int morreu = 0;
    int n_inimigos = 0;
    int y_nave;
    int x_nave;
    char mapa[LINHAS][COLUNAS];
    char tecla;
    
    // Limpa a tela
    system("cls");

    posicao_t inimigos[INIMIGO_MAX];    /// inimigos ficam na posicao

    posi = le_mapa(mapa, inimigos, &n_inimigos);    /// Passa a variavel do mapa, um vetor com tipo struct para botar a posicao dos inimigos
    pos.colunaX = posi.colunaX;                     /// e um ponteiro para a funcao me deizer quantos inimigos tem
    pos.linhaY = posi.linhaY;

    do{
        gotoxy(0,0); /// so para tirar um bugzinho esse gotoxy

        // Leitura do teclado
        if(kbhit()) {
            tecla = getch();
            le_movimento(tecla, &(pos), &vel);
        }

        pos.colunaX += vel;
        limite += vel;

        x_nave = pos.colunaX;
        y_nave = pos.linhaY;

        move_inimigos(mapa, inimigos, n_inimigos, y_nave, x_nave);

        detecta_colisao(mapa, pos, vel, &morreu);   /// passa o mapa, a struct com onde ele esta, a velocidade tem q ser usada para ver se
                                                    /// na proxima vai bater e um ponteiro para morreu
        
        mapa[pos.linhaY -1][pos.colunaX] = '@';      /// faz a nave ficar grande
        for(i = 0; i < 4; i++) {
            mapa[pos.linhaY][pos.colunaX +i] = '@';
        }
        limpa_rastro(tecla, pos, vel, mapa);

        // Imprime a tela
        imprime_tela(mapa, limite);

    } while(!morreu);
    
    printf("MORREU MORREU");
    return 0;
}
