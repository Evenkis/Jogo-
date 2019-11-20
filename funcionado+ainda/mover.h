typedef struct
{
    int linhaY, colunaX;
} posica_t;


void le_movimento(char c,posica_t *p,int *vel) //fiz uma função para ler tb
{                           ///recebe o que foi lido, ponteiros para as variaveis e para o lim que vai ser usado para print mapa.
    if(c == 'w')            // se c for w vai ter o y-- e impressão da nova matriz
        (*p).linhaY=((*p).linhaY)-1;                // tem q ser -- pq y é as linhas e com W quero q a nave suba, mas da para melhorar isso
    if(c == 's')
        (*p).linhaY=((*p).linhaY)+1;
    if(c == 'd')
        {
        (*vel)++; //aqui é a parte mais importante.
        }
    if(c == 'a')
    {
        (*vel)--;
    }
}




void limpa_rastro(char c,posica_t pos,int vel,char mapa[][COLUNAS])
{
    int i;
for(i=0; i<vel; i++)                               //ja fiz esse prog com modulos.
        {
            ///limpa o rastro
            mapa[pos.linhaY-1][pos.colunaX-i-1] = ' ';
            mapa[pos.linhaY][pos.colunaX-i-1] = ' ';
        }
        if(c=='s')
        {
            for(i=1; i<4; i++)
                mapa[pos.linhaY-1][pos.colunaX+i] = ' ';
            mapa[pos.linhaY-2][pos.colunaX-vel] = ' ';
        }
        if(c=='w')
            for(i = 0; i<4; i++)
                mapa[pos.linhaY+1][pos.colunaX+i-vel]=' ';

}

void detecta_colisao (char mapa[][COLUNAS],posica_t pos, int vel, int *morreu)

{   int i=0;
    if (mapa[pos.linhaY-1][pos.colunaX+vel] == 'C')
        *morreu = -1;
    for(i=0;i<4;i++)
    if ((mapa[pos.linhaY][pos.colunaX+vel+i] == 'C')) ///tem q add colisao com inimigos
        {                                             ///mas deve ser a mesma coisa.
            *morreu = -1;
        }
}

