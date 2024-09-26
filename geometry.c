#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "geometry.h"
#include "engine.h"
#include "config.h"

Vec2 projection(Vec3);
/*
 * Render Cuboid to SDL_Rendererer
 */
int CUBOID_Render(Cuboid* c) {

    int i; 
    for (i = 0; i < CUBOID_VERTICES; i++) {

        Vec3 p = c->points[i];
        Vec2 p_pr = projection(p); //projection of point p
        
        SDL_RenderDrawPoint(gRenderer, p_pr.x, p_pr.y);
    }

    return SUCCESS;
}

/*
 * Implement Weak Perspective Projection
 */
Vec2 projection(Vec3 vec) {
    // screen x and y
    Vec2 ret;
    ret.x = ((float)SCREEN_WIDTH/2 + (vec.x * FOV)/(vec.z + FOV) * 100);
    ret.y = ((float)SCREEN_HEIGHT/2 + (vec.y * FOV)/(vec.z + FOV) * 100);

    return ret;
}
