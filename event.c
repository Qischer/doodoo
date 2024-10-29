#include "engine.h"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

u32 box_w;
u32 box_h;

u32 pixels[];

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


    if ( e->type == SDL_KEYDOWN ) {
        SDL_KeyCode code = e->key.keysym.sym; 

        if (code == SDLK_m) {
            player->view = player->view == MAP ? FPS : MAP;
        }

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

    // Draw nearest point
    SDL_RenderDrawPoint(gRenderer, 
                        player->pos.x, player->pos.y);

    //Sweep 
    u32 ray_n = 320; 
    float phi = FOV / ray_n;

    u32 n = 2 * ray_n;
    u32 h_buffer[n];
    u8 shbuf[n];

    memset(&h_buffer, 0, sizeof(h_buffer));
    memset(&shbuf, 0, sizeof(shbuf));
    memset(pixels, 0, sizeof(pixels));

    vec2 sweep;
    sweep.x = dir_x;
    sweep.y = dir_y;

    u32 m = n/2;

    struct rayhit rh1;
    rh1 = raycast(sweep.x, sweep.y);
    render_ray(&rh1);

    h_buffer[m] = rh1.hit_dist;
    shbuf[m] = rh1.hit_side;

    int i;
    for (i = 0; i < ray_n; i++) {
        float x = dir_x * cosf(i*phi) - dir_y * sinf(i*phi);
        float y = dir_x * sinf(i*phi) + dir_y * cosf(i*phi);

        rh1 = raycast(x, y);
        render_ray(&rh1);

        h_buffer[m+i] = rh1.hit_dist * cosf(i*phi);
        shbuf[m+i] = rh1.hit_side;
    }

    for (i = 0; i < ray_n; i++) {
        float x = dir_x * cosf(-i*phi) - dir_y * sinf(-i*phi);
        float y = dir_x * sinf(-i*phi) + dir_y * cosf(-i*phi);

        rh1 = raycast(x, y);
        render_ray(&rh1);
        
        h_buffer[m-i] = rh1.hit_dist * cosf(i*phi);
        shbuf[m-i] = rh1.hit_side;
    }

    for (i = 0; i < n; i++) {
        if (h_buffer[i] <= 0) {continue;}
        renderVline(i, 69 * SCREEN_HEIGHT / h_buffer[i] + 50, shbuf[i]);
        printf("%d ", shbuf[i]);
    }

    printf("\n");

    SDL_RenderDrawLine(gRenderer, 
                       player->pos.x, player->pos.y, 
                       player->pos.x + s*player->dir.x,
                       player->pos.y + s*player->dir.y);
    
    renderMap();

    if (player->view == FPS) {

        SDL_UpdateTexture(gTexture, NULL, pixels, SCREEN_WIDTH * 4);
        SDL_RenderCopyEx(gRenderer, gTexture, NULL, NULL, 0.0, NULL, SDL_FLIP_VERTICAL);
    }
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

void renderVline(u32 w, u32 h, u8 sh) {

    if (h < 0) return;

    if (h > SCREEN_HEIGHT) h = SCREEN_HEIGHT;
    
    u32 h_offset = SCREEN_HEIGHT / 2;

    int i;
    for (i = 0; i < h/2; i++) {
        pixels[w + SCREEN_WIDTH* (h_offset+i)] = sh == 1 ? 0xFF1010FF : 0xDF1010FF; 
        pixels[w + SCREEN_WIDTH* (h_offset-i)] = sh == 1 ? 0xFF1010FF : 0xDF1010FF;   
    }
    return;
}

