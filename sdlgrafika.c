#include "main.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include "sdlgrafika.h"

//INICLIALIZ�L�S
void sdl_init(int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer)
{
    //MEGH�VJUK AZ SDL-T (HIBAESET�N HIBA�ZENET)
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    //MEGNYITJUK AZ ABLAKOT (HIBAESET�N HIBA�ZENET)
    SDL_Window *window = SDL_CreateWindow("SDL peldaprogram", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL)
    {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    //MEGJELEN�TJ�K AZ ABLAKOT(HIBAESET�N HIBA�ZENET)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL)
    {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
}

    Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
    }
