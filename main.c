#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#include "main.h"
#include "debugmalloc.h"
#include "palyakezeles.h"
#include "dinamikusmemoria.h"
#include "sdlgrafika.h"



int main(int argc, char *argv[])
{
    srand(time(0));

    int sejtmeret = 10;
    int eredetisejt=sejtmeret;


    SDL_Window *window;
    SDL_Renderer *renderer;
    sdl_init(ABLAKX, ABLAKY, &window, &renderer);

    int **tomb;
    tomb = lefoglal(ABLAKY/sejtmeret);
    Ures(tomb,sejtmeret);
    Kirajzol(renderer,tomb,sejtmeret);

    SDL_TimerID id = SDL_AddTimer(10, idozit, NULL);

    printf("Nyomj S gombot a menteshez!\nNyomj L gombot a betolteshez\nNyomj E gombot a resethez!\nNyomj R gombot a randomhoz!\nNyomj bal nyilat a lepeshez\
                        \nNyomj Space-t a folyamatos lepteteshez\nNyomj fel/le nyilat nagyitashoz/kicsinyeteshez!\nNyomj ESC-pet a kilepeshez\n");
    bool quit = false;
    bool folyamatos = false;
    int gombx=0,gomby=0;
    while (!quit)
    {

        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type)
        {

        case SDL_USEREVENT:
                if(folyamatos)
            {
                Torles(renderer,eredetisejt);
                tomb = Kovetkezo_allapot(tomb,eredetisejt);
                Kirajzol(renderer,tomb,eredetisejt);
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {

                gombx=event.button.x/sejtmeret;
                gomby=event.button.y/sejtmeret;
                if(gombx<ABLAKY/sejtmeret&&gomby<ABLAKY/sejtmeret)//EZ AZÉRT KELL, MERT HA A PÁLYÁN KÍVÜL KATTINTUNK AKKOR NE FOGLALJON FELESLEGES MEMÓRIÁT!
                {
                if( tomb[gomby][gombx]==0)
                {
                    tomb[gomby][gombx]=1;
                }
                else
                    tomb[gomby][gombx]=0;


                Torles(renderer,sejtmeret);
                Kirajzol(renderer,tomb,sejtmeret);
                SDL_RenderPresent(renderer);
                }
            }
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {

            case SDLK_e:
                folyamatos=false;
                Ures(tomb,sejtmeret);
                Torles(renderer,sejtmeret);
                Kirajzol(renderer,tomb,sejtmeret);
                break;
            case SDLK_r:
                folyamatos=false;
                TombFeltolt(tomb,ABLAKY/sejtmeret);
                Torles(renderer,sejtmeret);
                Kirajzol(renderer,tomb,sejtmeret);
                break;
            case SDLK_UP:

                if(sejtmeret<50)
                {
                    folyamatos=false;
                    Torles(renderer,sejtmeret);
                    sejtmeret+=5;
                    tomb = atmeretez(tomb,sejtmeret,eredetisejt);
                    Kirajzol(renderer,tomb,sejtmeret);
                    eredetisejt=sejtmeret;
                }

                break;
            case SDLK_DOWN:

                if(sejtmeret>10)
                {
                    folyamatos=false;
                    Torles(renderer,sejtmeret);
                    sejtmeret-=5;
                    tomb = atmeretez(tomb,sejtmeret,eredetisejt);
                    Kirajzol(renderer,tomb,sejtmeret);
                    eredetisejt=sejtmeret;
                }

                break;
            case SDLK_RIGHT:
                Torles(renderer,eredetisejt);
                tomb = Kovetkezo_allapot(tomb,eredetisejt);
                Kirajzol(renderer,tomb,eredetisejt);
                break;
            case SDLK_s:
                folyamatos=false;
                Mentes(tomb,sejtmeret);
                break;
            case SDLK_l:
                folyamatos=false;
                char input[15];
                printf("\nA betoltendo fajl neve(.txt kiterjesztes!):");scanf("%s",&input);
                tomb = atmeretez(tomb,meretbeolvas(input),eredetisejt);
                tomb = Betolt(tomb,input);
                Torles(renderer,eredetisejt);
                Kirajzol(renderer,tomb,meretbeolvas(input));
                eredetisejt= meretbeolvas(input);
                break;
            case SDLK_SPACE:
                    if(folyamatos)
                   folyamatos=false;
                   else
                    folyamatos=true;
                break;
            case SDLK_ESCAPE:
                quit=true;
                break;
            }
            break;

        case SDL_QUIT:
            quit = true;
            break;
        }

        SDL_RenderPresent(renderer);

    }
    SDL_Quit();
    felszabadit(tomb,eredetisejt);
    return 0;
}
