#include <SDL2/SDL.h>
#include <stdio.h>
#include "config.h"
#include "engine.h"

static u8 map[MAP_ROW * MAP_COL] = 
    {
        1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,
    };

/*
 * Main - main.c
 */
int main(int argc, char *argv[])
{
    if ( init() ) {
        printf("Error creating window! Err: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    eventInit();

    SDL_RenderPresent(gRenderer);

    SDL_Event e; 
    int quit = 0; 
    while( quit == 0 ){ 
        while( SDL_PollEvent( &e ) ){ 
            if( e.type == SDL_QUIT ) {
                quit = 1;
                break;
            }

            /*
            SDL_SetRenderDrawColor(gRenderer, 
                                   0, 0, 0, 
                                   SDL_ALPHA_OPAQUE);
            SDL_RenderClear(gRenderer);

            eventLoop(&e);

            SDL_RenderPresent(gRenderer);
            */
        }
    }
    
    closeWindow();

    return EXIT_SUCCESS;
}
