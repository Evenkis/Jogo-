#define VEL_TIRO 4
typedef struct
{
    int linhaY, colunaX;
} posica_t;

void le_movimento(char tecla, posica_t *p, int *vel,int *tiro)        //fiz uma funcao para ler tb
{
    ///recebe o que foi lido, ponteiros para as variaveis e para o lim que vai ser usado para print mapa.

    if(tecla == 'w')                        // se tecla for w, y--
        (*p).linhaY=((*p).linhaY)-1;

    else if(tecla == 's')
        (*p).linhaY=((*p).linhaY)+1;

    else if(tecla == 'd')
    {
        if((*vel) <= 3) //s� para n�o ser mais rapida q o tiro
            (*vel)++; //aqui a parte mais importante.
    }

    else if(tecla == 'a')
    {
//        if ((*vel)>1)
        (*vel)--;
    }
    else if(tecla == ' ')
    {
        (*tiro) = 1;
    }
}


void limpa_rastro(char tecla, posica_t pos, int vel, char mapa[][COLUNAS])
{
    int i;

    for(i = 0; i < vel; i++)    //ja fiz esse prog com modulos.
    {
        ///limpa o rastro
        mapa[pos.linhaY -1][pos.colunaX -i -1] = ' ';
        mapa[pos.linhaY][pos.colunaX -i -1] = ' ';
    }

    if(tecla == 's')
    {
        for(i = 1; i < 4; i++)
            mapa[pos.linhaY -1][pos.colunaX +i] = ' ';
        mapa[pos.linhaY -2][pos.colunaX -vel] = ' ';
    }

    if(tecla == 'w')
    {
        for(i = 0; i < 4; i++)
            mapa[pos.linhaY +1][pos.colunaX +i -vel] = ' ';
    }

}

void detecta_colisao (char mapa[][COLUNAS],posica_t pos, int vel, int *morreu)
{
    int i;

    if(mapa[pos.linhaY -1][pos.colunaX +vel] == 'C')
    {
        *morreu = -1;
    }

    for(i = 0; i < 4; i++)
    {
        if ((mapa[pos.linhaY][pos.colunaX +vel +i] == 'C'))
        {
            *morreu = -1;
        }
    }
}

void detecta_colisao_com_inimigo(char mapa[][COLUNAS],posica_t pos, int vel, int *morreu)
{
    int i;

    if(mapa[pos.linhaY -1][pos.colunaX +vel] == 'X')
    {
        *morreu = -1;
    }

    for(i = 0; i < 4; i++)                  ///mesma coisa q colisao com mapa
    {
        if ((mapa[pos.linhaY][pos.colunaX +vel +i] == 'X'))
        {
            *morreu = -1;
        }
    }
}

void gera_nave(char mapa[][COLUNAS],posica_t pos)
{
    int i=0;
    mapa[pos.linhaY -1][pos.colunaX] = '@';      /// faz a nave ficar grande
    for(i = 0; i < 4; i++)
    {
        mapa[pos.linhaY][pos.colunaX +i] = '@';
    }
}

void gera_tiro(char mapa[][COLUNAS],posicao_t nave,posicao_t *tiro )
{
    tiro->linhaY = nave.linhaY; //usei o "->" e o "*" para testar, mais como estudo para prova
    (*tiro).colunaX = nave.colunaX + 4;
    mapa[tiro->linhaY][tiro->colunaX] = '-'; //s� coloca um tiro no bico da nave

}

void faz_tiros_andarem(char mapa[][COLUNAS],posicao_t vet_tiros[],int n_tiros)
{
    int i,j,nao_vai;
    for(i=0; i<n_tiros; i++) //para todos os tiros j� dados, se n�o houver um espa�o (significando q ele bateu) ou um *
    {
        // que tb indica q ele morreu) o tiro anda com vel_tiro.
        if( (mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX] != ' ') && (mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX] != '*'))
            if( (mapa[vet_tiros[i].linhaY-1][vet_tiros[i].colunaX] != '*') )
            {
                for(j=0; j<VEL_TIRO; j++)
                    if(mapa[vet_tiros[i].linhaY][(vet_tiros[i].colunaX)+j] == 'C')
                    {
                        mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX] = ' ';
                        mapa[vet_tiros[i].linhaY][(vet_tiros[i].colunaX)-1] = ' ';
                        nao_vai = 1;
                    }

                if(nao_vai == 0)
                {
                    mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX] = ' ';

                    if( mapa[vet_tiros[i].linhaY][(vet_tiros[i].colunaX)-1] != '@' )
                    {
                        mapa[vet_tiros[i].linhaY][(vet_tiros[i].colunaX)-1] = ' ';
                    }

                    vet_tiros[i].colunaX = vet_tiros[i].colunaX + VEL_TIRO;
                    if(vet_tiros[i].colunaX >= COLUNAS)
                        vet_tiros[i].colunaX = vet_tiros[i].colunaX % COLUNAS;

                    if(vet_tiros[i].colunaX >= 410) //para sumir se estiver la no final
                    {
                        mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX] = ' ';
                        mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX-1] = ' ';
                    }
                    else        //limpa e faz o tiro andar
                    {
                        mapa[vet_tiros[i].linhaY][vet_tiros[i].colunaX] = '-';
                        mapa[vet_tiros[i].linhaY][(vet_tiros[i].colunaX)-1] = '-';
                    }
                }

            }
    }

}

void ve_se_tiro_bateu_inimigo(char mapa[][COLUNAS],posicao_t inimigos[],int n_inimigos,int *acertou)
{
    int i,k,l;
    for(i=0; i<n_inimigos; i++)
        for(k=0; k<2; k++)             ///ve se todas as casas dos inimigos n�o foram atigingidas
            for(l=0; l<2; l++)
                if( mapa[inimigos[i].linhaY - l][inimigos[i].colunaX + k] == '-')
                {
                    *acertou = 1;
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX] = '*';
                    mapa[inimigos[i].linhaY][inimigos[i].colunaX+1] = '*';  //coloca o * no inimigo por tres motivos
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX+1] = '*';//1) parece q explodiu
                    mapa[inimigos[i].linhaY-1][inimigos[i].colunaX] = '*';// 2) � um sinal q ele foi acertado para a fun��o q a
                    // apaga ele
                }                                                       // 3) pode ser uma maneira de add os pontos

}



