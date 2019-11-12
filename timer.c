#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h> // a bibilioteca que tem o negócio.





int main()
{
    struct timeval x,y;
    long sec;
    long sec_2;
    int lixo;
    gettimeofday(&x,NULL);
    sec = x.tv_sec;
    sec_2 = sec;
//    printf("%ld ",sec);
    int i=0;
    while((sec_2-sec) != 1)
        {
        gettimeofday(&y,NULL);
        sec_2 = y.tv_sec;
        i++;
        }
        printf("%d",i);

    return 0;
}
