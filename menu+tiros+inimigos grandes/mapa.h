#ifndef _DEFINES_

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <sys/time.h>

#define LINHAS 35
#define TAM 50
#define COLUNAS 415+1
#define COLUNAS_TELA 105
#define TELA_MAX 3710+1

#endif


typedef struct
{
    int linhaY, colunaX;
} posicao_t;

// Funcao gotoxy
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Funcao que le o mapa e detecta a nave e os inimigos
posicao_t le_mapa(char mapa[][COLUNAS], posicao_t inimigos[], int *ini, int sel)
{
    char nome_arq[TAM];
    int i, j;

    // Se 'Novo Jogo' for selecionado, le o nome do arquivo mapa
    if(sel == 0)
    {
        // Pega o nome do arquivo do mapa a ser aberto

        system("cls");  // limpa cmd

        gotoxy(20,14);
        printf("Informe o arquivo mapa que deseja ler: ");
        fgets(nome_arq, TAM, stdin);    /// recebe o nome do arquivo
        nome_arq[strlen(nome_arq) - 1] = '\0';
    }
    // Se 'Continuar' for selecionado, le o arquivo save.txt
    else if(sel == 1)
    {
        strcpy(nome_arq, "save.txt");
    }

    posicao_t nave; /// detecta e retorna a posicao da nave em uma struct

    // Abertura do arquivo como read-only
    FILE *arq=NULL;
    arq = fopen(nome_arq, "r");

    // Navegando no mapa
    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            // Copia o mapa para a variavel mapa
            mapa[i][j] = fgetc(arq);

            // Encontra a posicao da nave
            if (mapa[i][j] == '@')
            {
                nave.linhaY = i;
                nave.colunaX = j;
            }

            // Encontra a posicao dos inimigos
            if(mapa[i][j]== 'X')
            {
                inimigos[(*ini)].colunaX = j;
                inimigos[(*ini)].linhaY = i;
                (*ini)++;
            }
        }
    }

    // Fecha o arquivo
    fclose(arq);

    // Retorna a posicao da nave
    return nave;
}

//Imprime a tela (stringao)
void imprime_tela(char mapa[][COLUNAS],int lim)
{
    int i, j, k;
    char tela[TELA_MAX] = "";   // Cria o stringao vazio

    // Navega pelo mapa (ja inclui velocidade e limite e sla mais o que)
    for(i = 0; i < LINHAS; i++)
    {
        for(j = lim, k = lim; j < (COLUNAS_TELA + lim); j++)
        {
            if( (j+COLUNAS_TELA) >= COLUNAS  )
            {
                k = (j + COLUNAS_TELA - COLUNAS ); //o q faz o mapa voltar
            }
            else
                k = j ;

            // Le 1 char do mapa e concatena no stringao
            strncat(tela, &mapa[i][k], 1);
        }
        //Adiciona o \n no final de cada linha
        strcat(tela, "\n");
    }
    // Adiciona o \0 ao final do stringao
    strcat(tela, "\0");

    // Posiciona o cursor no inicio
    gotoxy(0,1);

    // Finalmente printa o stringao na tela
    printf("%s", tela);

    // Dorme um pouquinho
    Sleep(60);
}

int ve_se_inimigo_vai_bater_parede( posicao_t inimigo,char mapa[][COLUNAS],int subiu_desceu )
{
    //fun�a� bem simples que s� ve se o proximo movimento vai ter parede, pq se tiver ele n�o se move
    if(subiu_desceu == 1)
    {
        if(   (mapa[inimigo.linhaY-2][inimigo.colunaX])  == 'C') //se tiver parede n�o
            return 0;
        else
            return 1;
    }
    else
    {
        if ( (mapa[inimigo.linhaY+1][inimigo.colunaX]) == 'C')
            return 0;
        else
            return 1;

    }
}

void limpa_onde_o_inimigo_estava(char mapa[][COLUNAS],posicao_t inimigo)
{
    mapa[inimigo.linhaY][inimigo.colunaX+1] = ' ';
    mapa[inimigo.linhaY-1][inimigo.colunaX+1] = ' ';
    mapa[inimigo.linhaY-1][inimigo.colunaX] = ' '; //aquilo q vc tinha comentado de fazer fun��o para a parte de movimentar inimigo
    mapa[inimigo.linhaY][inimigo.colunaX] = ' ';
}

void coloca_inimigo_no_lugar_novo(char mapa[][COLUNAS],posicao_t inimigo)
{
    mapa[inimigo.linhaY][inimigo.colunaX+1] = 'X';
    mapa[inimigo.linhaY-1][inimigo.colunaX+1] = 'X';
    mapa[inimigo.linhaY-1][inimigo.colunaX] = 'X';
    mapa[inimigo.linhaY][inimigo.colunaX] = 'X'; //aquilo q vc tinha comentado de fazer fun��o para a parte de movimentar inimigo
}

// Funcao que move os inimigos
void move_inimigos(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int y_nave,int x_nave)
{
    int i = 0;
    int n_aleatorio;
    //    int subiu,desceu;
    srand(time(NULL));

        /* Essa � a fun��o mais complicada no programa, provavelmente, ela tem varias verifica��es e toma toda aparte de movimentar
         e arrumar o local que o inimigo foi, ela em um if bem externo que verifica se um inimigo deve andar, ele n�o deve andar se
        tiver sido acertado. a parte do '@' � para tenatr corrigir um bug e o espa�o em branco � para continuar n�o imprimindo ele*/

    for(i = 0; i<n_inimigos; i++)
    {
    //        subiu = 0;
    //        desceu = 0;
        if( (mapa[inimigos[i].linhaY][inimigos[i].colunaX] != '*') && (mapa[inimigos[i].linhaY][inimigos[i].colunaX] != ' ') )
            if((mapa[inimigos[i].linhaY][inimigos[i].colunaX] != '@'))
        {
            n_aleatorio = (rand()%(8)); /// gerar o numero aleatorio
            /// (n_aleatorio eh para probabilidade), se nao tiver na mesma linha e estiver proximo
            if(n_aleatorio < 3 && (y_nave != inimigos[i].linhaY) && ( (fabs(x_nave - inimigos[i].colunaX)) < 90))
            {
                /// se estiver a baixo, sobe
                if((y_nave - inimigos[i].linhaY)<0) ///para subir
                {
                    if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,1) == 1 )
                    {
                        // deleta a posicao antiga
                        limpa_onde_o_inimigo_estava(mapa,inimigos[i]);
                        /// 1 para subir -1 para descer
                        inimigos[i].linhaY = inimigos[i].linhaY - 1; // altera a posicao

                        coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);//bota na nova



    //                    subiu = 1;
                    }            //bota na nova


                }
                ///se nao, desce
                else
                {
                    if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,-1) == 1 )
                    {

                        limpa_onde_o_inimigo_estava(mapa,inimigos[i]);

                        inimigos[i].linhaY = inimigos[i].linhaY + 1;

                        coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);

    //                    desceu = 1;

                    }
                }
            }
            ///se nao passou em algum daqueles requisitos, tem 33% de chance de subir ou descer
            else
            {
                n_aleatorio = (rand() % 3);
                if(n_aleatorio == 1)
                {
                    if( (inimigos[i].linhaY) >= 3 )
                    {
                        if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,1) == 1 )
                        {

                            limpa_onde_o_inimigo_estava(mapa,inimigos[i]);

                            inimigos[i].linhaY = inimigos[i].linhaY - 1;

                            coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);

    //                        subiu = 1;
                        }
                    }
                }
                else if (n_aleatorio == 2)
                {
                    if(  (inimigos[i].linhaY) <= 33)
                    {
                        if(  ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,-1) == 1 )
                        {
                            limpa_onde_o_inimigo_estava(mapa,inimigos[i]);

                            inimigos[i].linhaY = inimigos[i].linhaY + 1;

                            coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);

    //                        desceu = 1;
                        }
                    }
                }
            }


            /// so anda para frente se estiver perto de 120 colunas
            if( (fabs(x_nave - inimigos[i].colunaX)) < 120)
            {
                /// faz todos os ininmigos andarem para frente
                {
                    limpa_onde_o_inimigo_estava(mapa,inimigos[i]);

                    inimigos[i].colunaX = inimigos[i].colunaX - 1;

                    coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);
                }
            }
            if(inimigos[i].colunaX <= 1)     // para quando chegar no come�o da matriz ir pro fim
                inimigos[i].colunaX = 415 - inimigos[i].colunaX;
        }

    }
}

void game_over(int pontos)
{
    // Limpa a tela
    system("cls");

    // Imprime "Game Over" no meio da tela
    gotoxy(47,14);
    printf("GAME OVER!");

    // Imprime a pontuacao
    gotoxy(43, 16);
    printf("Sua pontuacao: %d", pontos);

    gotoxy(35, 30);
    printf("Pressione qualquer tecla para sair.");

    // So pra deixar bonito
    gotoxy(0,36);
    printf(" ");

    Sleep(1000); // Pra evitar problemas 

    do{
        // Aguardar um hit no teclado para terminar o jogo
    } while(!kbhit());

    return;
}

void apaga_inimigos_acertados(char mapa[][COLUNAS], posicao_t inimigos[],int n_inimigos)
{
    int i;
    for(i=0; i<n_inimigos; i++)
        if( (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) ==  '*' ) //a parte de verificacao de acerto comentada na funcao
        {                                                             // "ve_se_tiro_bateu_inimigo"
            mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';

        }
}

// Funcao que salva o jogo no arquivo save.txt (Soh pode ter um save por vez. Salvar novamente sobrescreve o anterior)
void salvarJogo(char mapa[][COLUNAS]){
    int i, j, k;

    // Abertura do arquivo como escrita (overwrite)
    FILE *arq = NULL;
    arq = fopen("save.txt", "w");

    // Navega pelo mapa
    for(i = 0; i < LINHAS; i++){
        for(j = 0; j < COLUNAS; j++){
            // Copia o mapa para o arquivo (char por char) se não for nave nem inimigo
            if(mapa[i][j] != '@' && mapa[i][j] != 'X' && mapa[i][j] != '-'){
                fputc(mapa[i][j], arq);
            }

            // Se encontrar a nave (um @ acima e um na frente), bota somente um @ no arquivo
            if(mapa[i][j] == '@' && mapa[i-1][j] == '@' && mapa[i][j+1] == '@'){
                fputc('@', arq);
            }
            // Nas outras posicoes da nave, bota só um espaço
            else if(mapa[i][j] == '@'){
                fputc(' ', arq);
            }

            // Se encontrar o inimigo (um X acima e um na frente), bota somente um X no arquivo
            if(mapa[i][j] == 'X' && mapa[i-1][j] == 'X' && mapa[i][j+1] == 'X'){
                fputc('X', arq);
            }
            // Nas outras posicoes do inimigo, bota só um espaço
            else if(mapa[i][j] == 'X'){
                fputc(' ', arq);
            }

            // Condicao para nao gravar o tiro no mapa
            if(mapa[i][j] == '-'){
                fputc(' ', arq);
            }
        }
    }

    // Fecha o arquivo
    fclose(arq);

    // Imprime "Jogo Salvo" na tela
    gotoxy(46, 17);
    printf("Jogo Salvo!");
    Sleep(2000);

    return;
}