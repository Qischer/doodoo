#include "engine.h"
#include <math.h>
#include <stdio.h>

u32 box_w;
u32 box_h;

u8 signf(float);
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

    player->mapcord.x = player->pos.x / box_w;
    player->mapcord.y = player->pos.y / box_h;

    u8 s = 10;

    float speed = MOVE_SPEED;
    float th = speed * 0.0174f;

    float dir_x = player->dir.x;
    float dir_y = player->dir.y;

    float pos_x = player->pos.x;
    float pos_y = player->pos.y;

    vec2i delta;
    delta.x = box_w * sqrt(1 + ((dir_y * dir_y) / (dir_x * dir_x)));
    delta.y = box_h * sqrt(1 + ((dir_x * dir_x) / (dir_y * dir_y)));

    vec2i sides;
    sides.x = dir_x < 0 ? (u32)pos_x % box_w : box_w - ((u32)pos_x % box_w);
    sides.y = dir_y < 0 ? (u32)pos_y % box_h : box_h - ((u32)pos_y % box_h);

    vec2i sdist;
    sdist.x = sides.x * sqrt(1 + ((dir_y * dir_y) / (dir_x * dir_x)));
    sdist.y = sides.y * sqrt(1 + ((dir_x * dir_x) / (dir_y * dir_y)));


    printf("x: %d - y:%d\n", sides.x, sides.y);
    //printf("x: %.2f - y:%.2f\n", dir_x, dir_y);

    if ( e->type == SDL_KEYDOWN ) {
        SDL_KeyCode code = e->key.keysym.sym; 

        if (code == SDLK_w ){
            player->pos.x += speed * player->dir.x;
            player->pos.y += speed * player->dir.y;
        }
        if (code == SDLK_s ){
            player->pos.x -= speed * player->dir.x;
            player->pos.y -= speed * player->dir.y;
        }
        if (code == SDLK_a ){
            player->dir.x = dir_x * cosf(-th) - dir_y * sinf(-th);
            player->dir.y = dir_x * sinf(-th) + dir_y * cosf(-th);
        }
        if (code == SDLK_d ){
            player->dir.x = dir_x * cosf(th) - dir_y * sinf(th);
            player->dir.y = dir_x * sinf(th) + dir_y * cosf(th);
        }
    }

    SDL_RenderDrawPoint(gRenderer, 
                        player->pos.x, player->pos.y);
    
    SDL_RenderDrawPoint(gRenderer, 
                       player->pos.x + sdist.x*player->dir.x,
                       player->pos.y + sdist.x*player->dir.y);

    /*SDL_RenderDrawPoint(gRenderer, */
    /*                   player->pos.x + sdist.y*player->dir.x,*/
    /*                   player->pos.y + sdist.y*player->dir.y);*/

    SDL_RenderDrawLine(gRenderer, 
                       player->pos.x, player->pos.y, 
                       player->pos.x + s*signf(player->dir.x),
                       player->pos.y + s*signf(player->dir.y));
    
    renderMap();
    return SUCCESS;
}

void renderMap() {
    SDL_SetRenderDrawColor(gRenderer, 
                           0xAF, 0xAF, 0xAF, 
                           SDL_ALPHA_OPAQUE);

    box_w = SCREEN_WIDTH / MAP_COL;
    box_h = SCREEN_HEIGHT / MAP_ROW;

    vec2i box_pos = {0, 0};

    int i, j;
    for (i = 0; i < MAP_ROW; i++) {
        box_pos.y = i*box_h;
        for (j = 0; j < MAP_COL; j++) {

            if(map[i * MAP_COL + j] == 0) continue;
            
            SDL_Rect rect = {box_pos.x, box_pos.y, box_w, box_h};

            SDL_RenderDrawRect(gRenderer, &rect);
            box_pos.x = j*box_w;
        }
    }
}

u8 signf(float num) {
    return (u8) num / fabs(num);
};
