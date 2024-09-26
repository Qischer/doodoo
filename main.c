
#include <SDL2/SDL.h>
#include <stdio.h>
#include "config.h"
#include "engine.h"

/*
 * Main - main.c
 */
int main(int argc, char *argv[])
{
    if ( init() ) {
        printf("Error creating window! Err: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    /*if ( loadMedia("assets/fuckface.bmp") ) {*/
    /*    printf("Error loading media! Err: %s\n", SDL_GetError());*/
    /*    return EXIT_FAILURE;*/
    /*}*/
    /**/
    /*if ( SDL_UpdateWindowSurface(gWindow) ) {*/
    /*    printf("Error updating window! Err: %s\n", SDL_GetError());*/
    /*}*/

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

            eventLoop();
        }
    }
    
    closeWindow();

    return EXIT_SUCCESS;
}
