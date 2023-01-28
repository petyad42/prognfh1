#include "main.h"
#include "palyakezeles.h"
#include "dinamikusmemoria.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>


//ELMETI A JÁTÉK ÁLLÁSÁT EGY TXT-BE
void Mentes(int **tomb,int sejtmeret)
{
    FILE* fp;
    fp = fopen("mentes.txt","wt");
    fprintf(fp,"%d\n",sejtmeret);
    for(int i=0; i<ABLAKY/sejtmeret; i++)
    {
        for(int j=0; j<ABLAKY/sejtmeret; j++)
        {
            fprintf(fp,"%d",tomb[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    printf("Mentett!\n");
}
int meretbeolvas(char *utvonal){
    int meret=0;
    FILE* fp;
    fp = fopen(utvonal,"r");
    fscanf(fp, "\n%d",&meret);
    fclose(fp);
    return meret;
}

int **Betolt(int** tomb,char *utvonal){
    FILE* fp;
    fp = fopen(utvonal,"r");
    if(fp==NULL){
        printf("A fajl beolvasas sikertelen!");
        return;
    }
    int sejtmeret;
    fscanf(fp, "\n%d",&sejtmeret);
    printf("Sejtmeret: %d\n",sejtmeret);
    int tombmeret=ABLAKY/sejtmeret;
    int** uj = (int**)calloc(tombmeret,sizeof(int*));
    for(int i=0;i<tombmeret;i++)
        uj[i]=(int*)calloc(tombmeret,sizeof(int*));
    char szam=0;
    int szami=0;
    int oszlopit=0,sorit=-1;
    while(fscanf(fp, "%c", &szam) != EOF)
    {
        if(szam=='\n') {
            sorit++;
            oszlopit=0;
        }
        else{
            uj[sorit][oszlopit]=szam-'0';
            oszlopit++;
        }
    }
    fclose(fp);

    for(int i=0;i<tombmeret;i++)
        for(int j=0;j<tombmeret;j++)
            tomb[i][j]=uj[i][j];
    return tomb;
}

//FELTÖLTI A TÖMBÖT RANDOM SZÁMOKKAL 0 ÉS 1 KÖZÖTT
void TombFeltolt(int **tomb,int tombmeret)
{
    for(int i=0; i<tombmeret; i++)
    {
        for(int j=0; j<tombmeret; j++)
        {
            tomb[i][j]=rand()%2;

        }

    }
}

//TÖRLI AZ ABLAK TARTALMÁT
void Torles(SDL_Renderer *renderer,int sejtmeret)
{
    for(int i=0; i<ABLAKY/sejtmeret; i++)
    {
        for(int j=0; j<ABLAKY/sejtmeret; j++)
        {

            boxRGBA(renderer,(j+1)*sejtmeret,i*sejtmeret,j*sejtmeret,(i+1)*sejtmeret,0,0,0,255);

        }

    }
}
//KIRAJZOLJA A PÁLYÁT
void Kirajzol(SDL_Renderer *renderer,int **tomb,int meret)
{
    int tombmeret=ABLAKY/meret;
    for(int i=0; i<tombmeret; i++)
    {
        for(int j=0; j<tombmeret; j++)
        {
           // printf("%g ",tomb[i][j]);
            if(tomb[i][j]==0)
                rectangleRGBA(renderer,(j+1)*meret,i*meret,j*meret,(i+1)*meret,0,0,0,255);
            else if(tomb[i][j]==1)
                boxRGBA(renderer,(j+1)*meret,i*meret,j*meret,(i+1)*meret,255,255,255,255);
        }

    }
}

//KITÖLTI A PÁLYÁT 0-val
void Ures(int **tomb, int sejtmeret)
{
    for(int i=0; i<ABLAKY/sejtmeret; i++)
    {
        for(int j=0; j<ABLAKY/sejtmeret; j++)
        {
            tomb[i][j]=0;

        }

    }

}

int Szomszedokszama(int** tomb,int x,int y)
{
    int osszeg=0;
    for(int i=-1; i<2; i++)
    {
        for(int j=-1; j<2; j++)
        {
            osszeg+=tomb[x+i][y+j];
        }

    }
    osszeg-=tomb[x][y];
    return osszeg;
}

int **Kovetkezo_allapot(int** tomb,int sejtmeret)
{

    int szomszedszam,tombmeret=ABLAKY/sejtmeret;
    int** uj = (int**)calloc(tombmeret,sizeof(int*));
    for(int i=0;i<tombmeret;i++)
        uj[i]=(int*)calloc(tombmeret,sizeof(int*));

    for(int i=0; i<tombmeret;i++)
    {
        for(int j=0; j<tombmeret; j++)
        {

            if(i==0||i==tombmeret-1||j==0||j==tombmeret-1)
                uj[i][j]=0;
            else
            {
                szomszedszam=Szomszedokszama(tomb,i,j);
                if(tomb[i][j]==0&&szomszedszam==3)
                    uj[i][j]=1;
                else if(tomb[i][j]==1&&(szomszedszam<2||szomszedszam>3))
                    uj[i][j]=0;
                else
                    uj[i][j]=tomb[i][j];
            }

        }

    }

    for(int i=0;i<tombmeret;i++)
        for(int j=0;j<tombmeret;j++)
            tomb[i][j]=uj[i][j];
    return tomb;
}





