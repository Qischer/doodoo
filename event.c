#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdio.h>
#include "engine.h"

/*
 * event.c - Event Initialization and Loop
 */
int eventInit() {
    // Render 2D line
    SDL_SetRenderDrawColor(gRenderer, 
                           0xFF, 0xFF, 0xFF, 
                           SDL_ALPHA_OPAQUE);
    
    SDL_RenderDrawPoint(gRenderer, 
                        player->pos.x, player->pos.y);

    renderMap();
    return SUCCESS;
}

int eventLoop(SDL_Event* e) {
    SDL_SetRenderDrawColor(gRenderer, 
                           0xFF, 0xFF, 0xFF, 
                           SDL_ALPHA_OPAQUE);

    u8 s = 10;

    float speed = 5.0f;
    float th = 5 * 0.0174f;

    float dir_x = player->dir.x;
    float dir_y = player->dir.y;

    if ( e->type == SDL_KEYDOWN ) {
        switch ( e->key.keysym.sym ) {
            case SDLK_w:
                player->pos.x += speed * player->dir.x;
                player->pos.y += speed * player->dir.y;
                break;
            case SDLK_s:
                player->pos.x -= speed * player->dir.x;
                player->pos.y -= speed * player->dir.y;
                break;
            case SDLK_a:
                player->dir.x = dir_x * cosf(-th) - dir_y * sinf(-th);
                player->dir.y = dir_x * sinf(-th) + dir_y * cosf(-th);
                break;
            case SDLK_d:
                player->dir.x = dir_x * cosf(th) - dir_y * sinf(th);
                player->dir.y = dir_x * sinf(th) + dir_y * cosf(th);
                break;
        }
    }

    SDL_RenderDrawPoint(gRenderer, 
                        player->pos.x, player->pos.y);
    SDL_RenderDrawLine(gRenderer, 
                       player->pos.x, player->pos.y, 
                       player->pos.x + s*player->dir.x,
                       player->pos.y + s*player->dir.y);
    return SUCCESS;
}

void renderMap() {
    SDL_SetRenderDrawColor(gRenderer, 
                           0xDF, 0x32, 0xDF, 
                           SDL_ALPHA_OPAQUE);

    int box_w = SCREEN_WIDTH / MAP_COL;
    int box_h = SCREEN_HEIGHT / MAP_ROW;

    vec2i box_pos = {0, 0};

    int i, j;
    for (i = 0; i < MAP_ROW; i++) {
        for (j = 0; j < MAP_COL; j++) {


            printf("i:%d j:%d calc:%d map:%d\n",i,j, i * MAP_COL + j, map[i * MAP_COL + j]);

            if(map[i * MAP_COL + j] == 0) continue;
            
            SDL_Rect rect = {box_pos.x, box_pos.y, box_w, box_h};

            SDL_RenderDrawRect(gRenderer, &rect);
            box_pos.x = j*box_w;
        }
        box_pos.y = i*box_h;
    }
}
