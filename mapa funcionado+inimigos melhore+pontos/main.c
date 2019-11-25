#ifndef _DEFINES_                           ///eric

//#include "mapa.h" //mapa.h esta em menu.h
#include "menu.h"
#include "mover.h"

#define LINHAS 35
#define TAM 50
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#define INIMIGO_MAX 20
#define MAX_TIROS 3

#endif

int main()
{
    posica_t pos; //onde a posicao na nave fica realmente
    posicao_t vet_tiros[MAX_TIROS] = {0}; //vetor de tiros nave
    posicao_t posi,posi_nave; //posi && posi_nave p/ gambiarra
    posicao_t inimigos[INIMIGO_MAX];    /// inimigos ficam na posicao

    tiros_inimigos_t tiros[INIMIGO_MAX] = {0}; //vetor posição dos tiros, 1 tiro por inimigo

    int limite = 0; //pro mapa
    int vel = 1;
    int vidas = 3;
    int i = 0; //pros fors
    int tiro=0,contador_de_tiro=0,quantos_tiros=0,acertou=0; //coisa pro tiro funcionar
    int morreu = 0;
    int n_inimigos = 0;
    int y_nave;//gambiarra.org
    int x_nave;//gambiarra.org
    int x_nave_zero;//para ajustar o limite quando a nave chega no final
    int sel = 1;
    int *psel = &sel;
    int pontos = 0;
    char mapa[LINHAS][COLUNAS];
    char tecla; //o comando dado
    char nome_arq[TAM];

    // Limpa a tela
    system("cls");

    // Inicializa o menu (primeira impressao)
    printMenu(sel);

    // Selecao das opcoes do menu
    selecao(psel);

    // 'Sair' do jogo
    if(sel == 2)
    {
        // Limpa a tela
        system("cls");

        gotoxy(1,1);
        printf("Thank you for playing!\n");
        return 0;
    }

    // Inicia um novo jogo
    posi = le_mapa(mapa, inimigos, &n_inimigos, sel);  /// Passa a variavel do mapa, um vetor com tipo struct para botar a posicao dos inimigos
    pos.colunaX = posi.colunaX; //nave                 /// um ponteiro para a funcao me deizer quantos inimigos tem, e qual opcao do menu foi selecionada
    pos.linhaY = posi.linhaY;
    x_nave_zero = pos.colunaX;
    do
    {
        tecla = 'q';
        morreu =0;
        gotoxy(0,1); /// so para tirar um bugzinho esse gotoxy

        // Leitura do teclado
        if(kbhit())
        {
            tecla = getch();
            le_movimento(tecla, &(pos), &vel,&tiro);
            if(tecla == 'g'){
                salvarJogo(mapa, posi, inimigos, n_inimigos);
            }
        }
        gotoxy(0,0);
        printf("VIDAS:  %d  PONTOS: %d",vidas,pontos);
//        ///coloquei isso para tentar entender o bug q da quanto passa por um certo ponto (o q tem a bandeira)
//        printf("nave_linha = %d , nave_coluna = %d , limite = %d ", pos.linhaY, pos.colunaX, limite);

        pos.colunaX += vel;

        if((pos.colunaX + COLUNAS_TELA )>= COLUNAS )
        {
            pos.colunaX = (pos.colunaX + COLUNAS_TELA) % (COLUNAS-1);
            mapa[pos.linhaY][310] = ' ';
            mapa[(pos.linhaY)- 1][310] = ' '; ///só uns numeros magicos para funcionar o mapa 100%
            mapa[pos.linhaY][310-1] = ' ';
            mapa[(pos.linhaY)- 1][310-1] = ' ';
            mapa[pos.linhaY][310-2] = ' ';
            mapa[(pos.linhaY)- 1][310-2] = ' ';

        }
        //se vc for tentar arrumar o bug q faz o mapa dar aquela voltada eu ja te adianto q
        // mudar algumas coisas nas linhas 61-63 nao eh o caminho, eu tentei de tudo
        //deve ser alguma coisa relacionada com o limite
        limite += vel;

        if (limite >= COLUNAS ) //para arrumar o limite se der varias voltas
        {
            limite = pos.colunaX - x_nave_zero; ///só uns numeros magicos para funcionar o mapa 100%

        }
        x_nave = pos.colunaX;
        y_nave = pos.linhaY;

        if((i%3 == 0) && acertou ==0
            ) /// a cada 3 interacoes, isso sera verdadeiro e os inimigos vao se mover
            move_inimigos(mapa, inimigos, n_inimigos, y_nave, x_nave);

        if(acertou == 1){
            apaga_inimigos_acertados(mapa,inimigos,n_inimigos);
        }

        acertou = 0; //acertou eh zerado dps de ser usado em apaga_inimigos

        detecta_colisao(mapa, pos, vel, &morreu);
        /// passa o mapa, a struct com onde ele esta, a velocidade tem q ser usada para ver se
        /// na proxima vai bater e um ponteiro para morreu


        if(morreu == 0) //uma optimizada de leve
            detecta_colisao_com_inimigo(mapa, pos, vel, &morreu);

        gera_nave(mapa,pos); //adicionei isso para ficar mais alto nivel

        if(tiro == 1)
        {
            quantos_tiros++; //para passar quantos tiros ja foram dados e poder movelos

            contador_de_tiro++;
            contador_de_tiro %= MAX_TIROS; ///gera os tiros (3 no max)

            if (quantos_tiros > MAX_TIROS)
                quantos_tiros = MAX_TIROS;

            mapa[vet_tiros[contador_de_tiro].linhaY][vet_tiros[contador_de_tiro].colunaX] = ' ';

            //limpa o tiro antigo

            if ( mapa[vet_tiros[contador_de_tiro].linhaY][(vet_tiros[contador_de_tiro].colunaX) - 1] != '@')
                mapa[vet_tiros[contador_de_tiro].linhaY][(vet_tiros[contador_de_tiro].colunaX)-1] = ' ';

            posi_nave.linhaY = pos.linhaY;
            posi_nave.colunaX = pos.colunaX;

            gera_tiro(  mapa,  posi_nave  , &(vet_tiros[contador_de_tiro])   );
        }

        faz_tiros_andarem(mapa,vet_tiros,quantos_tiros);

        ve_se_tiro_bateu_inimigo(mapa,inimigos,n_inimigos,&acertou);

        limpa_rastro(tecla, pos, vel, mapa);

        arruma_bug_de_inimigo_nao_sumindo(mapa,inimigos,n_inimigos);

//        inimigos_atiram(mapa,tiros,inimigos,n_inimigos);  //WIP

        conta_pontos(n_inimigos,mapa,&pontos);

        // Imprime a tela
        imprime_tela(mapa, limite);
        i++;
        tiro=0;
        if(morreu == -1)
        {
            Beep(900,900);
//            printf("\a\a");
            Sleep(2000);
            vidas--;
            coloca_a_nave_no_meio_e_arruma_mapa(mapa,pos,&(pos).linhaY);
        }

    }
    while(vidas !=  0 && (pontos != (n_inimigos * 10)));

    conta_pontos(n_inimigos,mapa,&pontos);
    game_over(pontos,n_inimigos);

    return 0;
}
