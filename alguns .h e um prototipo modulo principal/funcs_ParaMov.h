



void le_movimento(char c,int *px,int *py,int *lim) //fiz uma função para ler tb
{                           ///recebe o que foi lido, ponteiros para as variaveis e para o lim que vai ser usado para print mapa.
    if(c == 'w')            // se c for w vai ter o y-- e impressão da nova matriz
        *py=(*py)-1;                // tem q ser -- pq y é as linhas e com W quero q a nave suba, mas da para melhorar isso
    if(c == 's')
        *py=(*py)+1;
    if(c == 'd')
        {
        *px=(*px)+1;
        *lim = (*lim) + 1; //aqui é a parte mais importante.
        }
    if(c == 'a')
        *px=(*px)-1; //já que agora o mapa anda e ainda não fizemos o jogo nas duas direções isso pode ser tirado.
}
