#include <stdlib.h>
#include "engine.h"

SDL_Window* gWindow; 
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;

struct player* player;

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

    gTexture = SDL_CreateTexture(gRenderer,
                                 SDL_PIXELFORMAT_ABGR8888,
                                 SDL_TEXTUREACCESS_STREAMING,
                                 SCREEN_WIDTH,
                                 SCREEN_HEIGHT);
    if ( gTexture == NULL ) {
        return ERROR;
    }

    //memset(pixels, 0, sizeof(pixels));

    player = malloc(sizeof(struct player));
    
    vec2 pldir = {1.0f, 1.0f};
    vec2 plpos = {(float) SCREEN_WIDTH / 2, (float) SCREEN_HEIGHT / 2};

    player->dir = pldir;
    player->pos = plpos;

    return SUCCESS;
}

/*
 * Close Window and Free Resources
 */
void closeWindow() {
    printf("Closing Window.\n");
    SDL_DestroyWindow(gWindow);
    free(player);
    SDL_Quit();
}


