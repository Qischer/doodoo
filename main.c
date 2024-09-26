
#include <SDL2/SDL.h>
#include <stdio.h>
#include "config.h"

int init();
int loadMedia(const char*);
void closeWindow();

SDL_Window* gWindow;
SDL_Surface* gSurface;

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

    gSurface = SDL_GetWindowSurface(gWindow);

    return SUCCESS;
}

int loadMedia(const char* filepath) {
    
    SDL_Surface* face = SDL_LoadBMP(filepath);

    if (face == NULL) {
        return ERROR;
    }

    SDL_BlitSurface(face, NULL, gSurface, NULL);
    return  SUCCESS;
}

void closeWindow() {
    printf("Closing Window.\n");
    SDL_FreeSurface(gSurface);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

/*
 * Main - main.c
 */
int main(int argc, char *argv[])
{
    if ( init() ) {
        printf("Error creating window! Err: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if ( loadMedia("assets/fuckface.bmp") ) {
        printf("Error loading media! Err: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    if ( SDL_UpdateWindowSurface(gWindow) ) {
        printf("Error updating window! Err: %s\n", SDL_GetError());
    }

    SDL_Event e; 
    int quit = 0; while( quit == 0 ){ while( SDL_PollEvent( &e ) ){ if( e.type == SDL_QUIT ) quit = 1; } }
    
    closeWindow();

    return EXIT_SUCCESS;
}
