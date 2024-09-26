#include <SDL2/SDL.h>
#include "engine.h"
#include "types.h"

/*
 * event.c - Event Initialization and Loop
 */

int eventInit() {

    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    
    int err; 
    // Render 2D line
    Vec2 p1 = { 100.0f, 100.0f };
    Vec2 p2 = { 200.0f, 200.0f };
    
    err = SDL_RenderDrawPoint(gRenderer, p1.x, p1.y);
    if ( err ) {
        return ERROR;
    }

    err = SDL_RenderDrawPoint(gRenderer, p2.x, p2.y);
    if ( err ) {
        return ERROR;
    }
    
    return SUCCESS;
}

int eventLoop() {
    return SUCCESS;
}
