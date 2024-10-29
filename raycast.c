#include "engine.h"
#include <stdio.h>

struct rayhit raycast(float dir_x, float dir_y) {

    struct rayhit hit;

    float pos_x = player->pos.x;
    float pos_y = player->pos.y;

    vec2i delta;
    delta.x = box_w * sqrt(1 + ((dir_y * dir_y) / (dir_x * dir_x)));
    delta.y = box_h * sqrt(1 + ((dir_x * dir_x) / (dir_y * dir_y)));

    hit.dir.x = dir_x;
    hit.dir.y = dir_y;

    vec2i sides;
    sides.x = dir_x < 0 ? (u32)pos_x % box_w : box_w - ((u32)pos_x % box_w);
    sides.y = dir_y < 0 ? (u32)pos_y % box_h : box_h - ((u32)pos_y % box_h);

    vec2i sdist;
    sdist.x = sides.x * sqrt(1 + ((dir_y * dir_y) / (dir_x * dir_x))); // distance from player to col
    sdist.y = sides.y * sqrt(1 + ((dir_x * dir_x) / (dir_y * dir_y))); // distance from player to row
    
    hit.hit = 0;
    hit.cord.x = player->mapcord.x;
    hit.cord.y = player->mapcord.y;

    hit.side_dist.x = sdist.x;
    hit.side_dist.y = sdist.y;
    
    while (1) {
        u32 idx = hit.cord.x + hit.cord.y * MAP_COL; 
        if (map[idx] == 1) {hit.hit = 1; break;}

        if (hit.side_dist.x <= hit.side_dist.y) {
            hit.side_dist.x += delta.x;
            hit.cord.x += signf(dir_x);
        }
        else {
            hit.side_dist.y += delta.y;
            hit.cord.y += signf(dir_y);
        }

    }

    if (hit.side_dist.x - delta.x > hit.side_dist.y - delta.y) {
        
        hit.hit_dist = hit.side_dist.x - delta.x;
        hit.hit_side = 1;
    }
    else {
        hit.hit_dist = hit.side_dist.y - delta.y;
        hit.hit_side = 0;
    }

    //hit.hit_dist = max(hit.side_dist.x - delta.x, hit.side_dist.y - delta.y);
    
    //hit.hit_side = (hit.side_dist.x - delta.x) < (hit.side_dist.y - delta.y) ? 1 : 0;
    
    return hit;
}

void render_ray(struct rayhit* hit) {
    
    float _sn = hit->dir.y / sqrt(hit->dir.y*hit->dir.y + hit->dir.x*hit->dir.x);
    float _cs = hit->dir.x / sqrt(hit->dir.y*hit->dir.y + hit->dir.x*hit->dir.x); 

    SDL_SetRenderDrawColor(gRenderer, 
                           0xAF, 0x00, 0x00, 
                           SDL_ALPHA_OPAQUE);

    SDL_RenderDrawLine(gRenderer, 
                       player->pos.x, player->pos.y, 
                       player->pos.x + hit->hit_dist*_cs,
                       player->pos.y + hit->hit_dist*_sn);


    SDL_SetRenderDrawColor(gRenderer, 
                           0xAF, 0xAF, 0xAF, 
                           SDL_ALPHA_OPAQUE);
}
