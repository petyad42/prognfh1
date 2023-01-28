#ifndef PALYAKEZELES_H_INCLUDED
#define PALYAKEZELES_H_INCLUDED
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

void Mentes(int **tomb,int sejtmeret);
int meretbeolvas(char *utvonal);
int **Betolt(int** tomb,char *utvonal);
void TombFeltolt(int **tomb,int tombmeret);
void Torles(SDL_Renderer *renderer,int sejtmeret);
void Kirajzol(SDL_Renderer *renderer,int **tomb,int sejtmeret);
void Ures(int **tomb, int sejtmeret);
int Szomszedokszama(int** tomb,int x,int y);
int** Kovetkezo_allapot(int** tomb,int meret);





#endif // PALYAKEZELES_H_INCLUDED
