#include <stdio.h>
#include <stdlib.h>
#include "debugmalloc.h"
#include "dinamikusmemoria.h"
#include "main.h"


int** lefoglal(int tmeret)
{
    int** uj;
    uj = (int**)malloc(tmeret*sizeof(int*));
    for(int i=0; i<tmeret; i++)
        uj[i]=(int*)malloc(tmeret*sizeof(int));
    return uj;
}



void felszabadit(int** tomb,int meret)
{
    int tombmeret=ABLAKY/meret;
    for(int i=0; i<tombmeret; i++)
    {
        free(tomb[i]);
    }
    free(tomb);
}



int** atmeretez(int **tomb,int ujmeret,int meret)
{
    int ujtombmeret=ABLAKY/ujmeret;
    int tombmeret=ABLAKY/meret;
    int** temp = NULL;

    if(ujtombmeret<tombmeret)
        for(int i=ujtombmeret; i<tombmeret; i++)
            free(tomb[i]);

    temp = (int**)realloc ( tomb, ujtombmeret * sizeof(int*));
    tomb = temp;
    for ( int i = tombmeret; i < ujtombmeret; i++) //AZÉRT KELL NULLAL KITÖLTENI, MERT KÜLÖNBEN ÚGY ÉRZÉKELI A KÖVETKEZÕ ÁTMÉRETEZENDÕ TÖMBÖT, HOGY NINCS LEFOGLALVA.
        tomb[i] = NULL;

    for ( int i = 0; i < ujtombmeret; i++)
    {
        tomb[i] = (int*)realloc (tomb[i], ujtombmeret * sizeof(int));
        for(int j= 0; j< ujtombmeret; j++)
            tomb[i][j]=0;
    }

    return tomb;
}





