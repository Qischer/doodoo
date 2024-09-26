#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "engine.h"
#include "config.h"

SDL_Window* gWindow; 
SDL_Surface* gSurface;
SDL_Renderer* gRenderer;
/*
 * Initialize Window
 */
int init() {
    
    if ( SDL_Init(SDL_INIT_VIDEO) < 0) {
        return ERROR;
    }

    gWindow = SDL_CreateWindow("DooDoo", 
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT, 
                               SDL_WINDOW_SHOWN);

    if ( gWindow == NULL ) {
        return ERROR;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if ( gRenderer == NULL ) {
        return ERROR;
    }

    gSurface = SDL_GetWindowSurface(gWindow);
    if ( gSurface == NULL ) {
        return ERROR;
    }

    return SUCCESS;
}

/*
 * Load Media to Surface
 */
int loadMedia(const char* filepath) {
    
    SDL_Surface* face = SDL_LoadBMP(filepath);

    if (face == NULL) {
        return ERROR;
    }

    SDL_BlitSurface(face, NULL, gSurface, NULL);
    return  SUCCESS;
}

/*
 * Close Window and Free Resources
 */
void closeWindow() {
    printf("Closing Window.\n");
    SDL_FreeSurface(gSurface);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}


