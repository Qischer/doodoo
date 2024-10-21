#include "engine.h"

struct rayhit raycast(float dir_x, float dir_y) {

    struct rayhit hit;

    float pos_x = player->pos.x;
    float pos_y = player->pos.y;

    float _sn = dir_y / sqrt(dir_y*dir_y + dir_x*dir_x);
    float _cs = dir_x / sqrt(dir_y*dir_y + dir_x*dir_x); 


    vec2i delta;
    delta.x = box_w * sqrt(1 + ((dir_y * dir_y) / (dir_x * dir_x)));
    delta.y = box_h * sqrt(1 + ((dir_x * dir_x) / (dir_y * dir_y)));

    vec2i sides;
    sides.x = dir_x < 0 ? (u32)pos_x % box_w : box_w - ((u32)pos_x % box_w);
    sides.y = dir_y < 0 ? (u32)pos_y % box_h : box_h - ((u32)pos_y % box_h);

    vec2i sdist;
    sdist.x = sides.x * sqrt(1 + ((dir_y * dir_y) / (dir_x * dir_x))); // distance from player to col
    sdist.y = sides.y * sqrt(1 + ((dir_x * dir_x) / (dir_y * dir_y))); // distance from player to row
    
    hit.hit = 0;
    hit.cord.x = player->mapcord.x;
    hit.cord.y = player->mapcord.y;

    hit.dist.x = sdist.x;
    hit.dist.y = sdist.y;
    
    while (1) {
        u32 idx = hit.cord.x + hit.cord.y * MAP_COL; 
        if (map[idx] == 1) {hit.hit = 1; break;}

        if (hit.dist.x <= hit.dist.y) {
            hit.dist.x += delta.x;
            hit.cord.x += signf(dir_x);
        }
        else {
            hit.dist.y += delta.y;
            hit.cord.y += signf(dir_y);
        }

    }
    
    return hit;
}
