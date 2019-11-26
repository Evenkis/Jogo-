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
#define VEL_TIRO_INIMIGO 3

#endif


typedef struct
{
    int linhaY, colunaX;
} posicao_t;

typedef struct
{
    int colunaX_tiro;
    int linhaY_tiro;
    int quantas_casas_andou;

} tiros_inimigos_t;

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
        for(j = lim+1; j < (COLUNAS_TELA + lim); j++)
        {
            if( (j+COLUNAS_TELA) >= COLUNAS )
            {
                k = ((j + COLUNAS_TELA) % COLUNAS ); //o q faz o mapa voltar
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

    // Dorme um pouquinho :D
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
    else if (subiu_desceu == -1)
    {
        if ( (mapa[inimigo.linhaY+1][inimigo.colunaX]) == 'C')
            return 0;
        else
            return 1;

    }
    else
    {
        if ( (mapa[inimigo.linhaY][inimigo.colunaX-1]) == 'C' ||(mapa[inimigo.linhaY-1][inimigo.colunaX-1]) == 'C' )
            return 0;
        else
            return 1;
    }
}

void limpa_onde_o_inimigo_estava(char mapa[][COLUNAS],posicao_t inimigo)
{
    mapa[inimigo.linhaY][inimigo.colunaX+1] = ' ';
    mapa[inimigo.linhaY-1][inimigo.colunaX+1] = ' ';
    mapa[inimigo.linhaY-1][inimigo.colunaX] = ' '; //aquilo q vc tinha comentado de fazer func para a parte de movimentar inimigo
    mapa[inimigo.linhaY][inimigo.colunaX] = ' ';
//    mapa[inimigo.linhaY][(inimigo.colunaX) - 1] = ' ';
}

void coloca_inimigo_no_lugar_novo(char mapa[][COLUNAS],posicao_t inimigo)
{
    mapa[inimigo.linhaY][inimigo.colunaX+1] = 'X';
    mapa[inimigo.linhaY-1][inimigo.colunaX+1] = 'X';
    mapa[inimigo.linhaY-1][inimigo.colunaX] = 'X';
    mapa[inimigo.linhaY][inimigo.colunaX] = 'X'; //aquilo q vc tinha comentado de fazer fun��o para a parte de movimentar inimigo
}



void limpa_rastro_tiro_inimigo(char mapa[][COLUNAS],posicao_t inimigo,int subiu_desceu)
{
    if(subiu_desceu == 1)
        mapa[inimigo.linhaY - 1][inimigo.colunaX - 1] = ' ';
    if(subiu_desceu == -1)
        mapa[inimigo.linhaY + 1][inimigo.colunaX - 1] = ' ';
}
// Funcao que move os inimigos
void move_inimigos(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int y_nave,int x_nave)
{
    int i = 0;
    int n_aleatorio;
    //    int subiu,desceu;
    srand(time(NULL));

    /* Essa e a fun��o mais complicada no programa, provavelmente, ela tem varias verifica��es e toma toda aparte de movimentar
     e arrumar o local que o inimigo foi, ela em um if bem externo que verifica se um inimigo deve andar, ele naoo deve andar se
    tiver sido acertado. a parte do '@' wh para tenatr corrigir um bug e o espa�o em branco ' ' para continuar naoo imprimindo ele*/

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

//                            if(mapa[inimigos[i].linhaY][inimigos[i].colunaX - 1] == '~')
//                                limpa_rastro_tiro_inimigo(mapa,inimigos[i],1);                             /// 1 para subir -1 para descer

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
//
//                            if(mapa[inimigos[i].linhaY][inimigos[i].colunaX - 1] == '~')
//                                limpa_rastro_tiro_inimigo(mapa,inimigos[i],-1);

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

//                                if(mapa[inimigos[i].linhaY][inimigos[i].colunaX - 1] == '~')
//                                    limpa_rastro_tiro_inimigo(mapa,inimigos[i],1);

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

//                                if(mapa[inimigos[i].linhaY][inimigos[i].colunaX - 1] == '~')
//                                    limpa_rastro_tiro_inimigo(mapa,inimigos[i],-1);

                                inimigos[i].linhaY = inimigos[i].linhaY + 1;

                                coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);

                                //                        desceu = 1;
                            }
                        }
                    }
                }


                /// so anda para frente se estiver perto de 120 colunas
//                if( (fabs(x_nave - inimigos[i].colunaX)) < 120)
                {
                    /// faz todos os ininmigos andarem para frente
                    if(ve_se_inimigo_vai_bater_parede(inimigos[i],mapa,3) == 1)
                    {
                        limpa_onde_o_inimigo_estava(mapa,inimigos[i]);

                        inimigos[i].colunaX = inimigos[i].colunaX - 1;

                        coloca_inimigo_no_lugar_novo(mapa,inimigos[i]);
                    }
                }
                if(inimigos[i].colunaX == 0)
                {
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ' ;
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ' ;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ' ;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ' ;

                    // para quando chegar no come�o da matriz ir pro fim

                    inimigos[i].colunaX = 310;

                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = 'X' ;
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = 'X' ;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = 'X' ;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = 'X' ;
                }
            }

    }
}
void musica_vitoria()
{
    Beep(987,53);
    Beep(987,53);
    Beep(987,53);
    Beep(987,428);
    Beep(784,428);
    Beep(880,428);
    Beep(987,107);
    Beep(880,107);
    Beep(987,857);
    Beep(740,428);
    Beep(659,428);
    Beep(740,428);
    Beep(659,107);
    Beep(880,428);
    Beep(880,107);
    Beep(830,428);
    Beep(880,107);
    Beep(830,428);
    Beep(830,107);
    Beep(740,428);
    Beep(659,428);
    Beep(622,428);
    Beep(659,107);
    Beep(554,1714);
    Beep(740,428);
    Beep(659,428);
    Beep(740,428);
    Beep(659,107);
    Beep(880,428);
    Beep(880,107);
    Beep(830,428);
    Beep(880,107);
    Beep(830,428);
    Beep(830,107);
    Beep(740,428);
    Beep(659,428);
    Beep(740,428);
    Beep(880,107);
    Beep(987,1314);
}



void game_over(int pontos,int n_inimigos)
{
    // Limpa a tela
    system("cls");

    // Imprime "Game Over" no meio da tela
    gotoxy(47,14);
    if(pontos == n_inimigos*10)
    {
        printf("YOU WIN");
        musica_vitoria();
    }
    else
        printf("GAME OVER!");

    // Imprime a pontuacao
    gotoxy(43, 16);
    printf("Sua pontuacao: %d", pontos);

    Sleep(1000);

    gotoxy(35, 30);
    printf("Pressione qualquer tecla para sair.");

    // So pra deixar bonito
    gotoxy(0,36);
    printf(" ");

    Sleep(1000); // Pra evitar problemas

    do
    {
        // Aguardar um hit no teclado para terminar o jogo
    }
    while(!kbhit());

    return;
}

void apaga_inimigos_acertados(char mapa[][COLUNAS], posicao_t inimigos[],int n_inimigos)
{
    int i;
    for(i=0; i<n_inimigos; i++)
        if( (mapa[inimigos[i].linhaY][inimigos[i].colunaX]) ==  '*' ) //a parte de verificacao de acerto comentada na funcao
        {
            // "ve_se_tiro_bateu_inimigo"
            mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY][(inimigos[i].colunaX) - 1] = ' ';
        }
}

// Funcao que salva o jogo no arquivo save.txt (Soh pode ter um save por vez. Salvar novamente sobrescreve o anterior)
void salvarJogo(char mapa[][COLUNAS], posicao_t pos, posicao_t inimigos[], int n_inimigos)
{
    int i, j, k;

    // Abertura do arquivo como escrita (overwrite)
    FILE *arq = NULL;
    arq = fopen("save.txt", "w");

    // Navega pelo mapa
    for(i = 0; i < LINHAS; i++)
    {
        for(j = 0; j < COLUNAS; j++)
        {
            // Copia o mapa para o arquivo (char por char)
            fputc(mapa[i][j], arq);

            // Verifica se a coordenada atual eh a nave
            if(i == pos.colunaX && j == pos.linhaY)
            {
                fputc('@', arq);
            }
            else
            {
                // Verifica se existe algum inimigo na posicao atual
                for(k = 0; k < n_inimigos; k++)
                {
                    if(i == (inimigos[k]).colunaX && j == (inimigos[k]).linhaY)
                    {
                        fputc('X', arq);
                    }
                }
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


void arruma_bug_de_inimigo_nao_sumindo(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos)
{
    int i;
    for(i=0; i<n_inimigos; i++)
    {
        if ( mapa[inimigos[i].linhaY][inimigos[i].colunaX] == ' ')
        {
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
        }
        else if ( mapa[(inimigos[i].linhaY)-1][inimigos[i].colunaX] == ' ')
        {
            mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
        }
        else if ( mapa[(inimigos[i].linhaY)][inimigos[i].colunaX+1] == ' ')
        {
            mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
        }
        else if ( mapa[(inimigos[i].linhaY)-1][inimigos[i].colunaX+1] == ' ')
        {
            mapa[inimigos[i].linhaY][inimigos[i].colunaX] = ' ';
            mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = ' ';
            mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = ' ';
        }
    }

}


void conta_pontos(int n_inimigos, char mapa[][COLUNAS], int *pontos)
{
    int i,j,contador=0;
    *pontos = 0;
//    int verificar=0;

    for(i=0; i<LINHAS; i++)
        for(j=0; j<COLUNAS; j++)
            if(  mapa[i][j] == 'X' )
            {
                contador++;
            }
    contador=contador/4;
    *pontos = n_inimigos - contador;
    *pontos = (*pontos)*10;
}

void inimigos_atiram(char mapa[][COLUNAS],tiros_inimigos_t tiros[],posicao_t inimigos[],int n_inimigos)
{
    int i,n_aleatorio;
    srand(time(NULL));

    for(i=0; i<n_inimigos; i++)
    {
        n_aleatorio = rand()%100;
        if(mapa[inimigos[i].linhaY][inimigos[i].colunaX] == 'X')  //se tiver vivo
        {
            if( mapa[inimigos[i].linhaY][inimigos[i].colunaX - 1] != '~' && (n_aleatorio<23)) //e não tiver um tiro já
            {
                //20% de chance do inimigo atirar
                if(mapa[tiros[i].linhaY_tiro][tiros[i].colunaX_tiro] == '~')
                {
                    mapa[tiros[i].linhaY_tiro][tiros[i].colunaX_tiro] = ' ';
                }

                tiros[i].colunaX_tiro = inimigos[i].colunaX;  //coloca um tiro
                tiros[i].linhaY_tiro = inimigos[i].linhaY;

                tiros[i].colunaX_tiro = tiros[i].colunaX_tiro - 1;

                mapa[tiros[i].linhaY_tiro][tiros[i].colunaX_tiro] = '~';
            }

        }

    }
}
void tiros_andam(char mapa[][COLUNAS],tiros_inimigos_t *tiro)
{

    srand(time(NULL));

    if(  (mapa[tiro->linhaY_tiro][tiro->colunaX_tiro ]) == '~') //se tiver um tiro
    {
        mapa[tiro->linhaY_tiro][tiro->colunaX_tiro] = ' '; //apaga esse tiro

        if( mapa[tiro->linhaY_tiro][tiro->colunaX_tiro - VEL_TIRO_INIMIGO] == 'C') //se for bater na parede some
            mapa[tiro->linhaY_tiro][tiro->colunaX_tiro] = ' ';
        else
        {
            tiro->colunaX_tiro = tiro->colunaX_tiro - VEL_TIRO_INIMIGO; //mexe ele

            if(tiro->colunaX_tiro <= 2)
                tiro->colunaX_tiro = 310; //para ir pro final se chegar no comeco

            mapa[tiro->linhaY_tiro][tiro->colunaX_tiro] = '~'; // e coloca ele no lugar novo
        }
    }

}
