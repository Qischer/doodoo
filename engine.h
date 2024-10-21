#include <SDL2/SDL.h> 
#include <stdint.h>
#include <math.h>

#include "geometry.h"
#include "raycast.h"
#include "config.h"

//Macros
#define max(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
  _a > _b ? _a : _b; })

#define min(a,b) \
({ __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
  _a < _b ? _a : _b; })

#define signf(n) ({n < 0 ? -1: 1;})

// Type redefinitions
typedef uint8_t u8;
typedef int8_t i8;
typedef uint32_t u32;

// Engine header
extern int init(void);
extern int loadMedia(const char*);
extern void closeWindow(void);


//In event.c
extern int eventInit(void);
extern int eventLoop(SDL_Event* e);
extern void renderMap();

//Global variables
extern SDL_Window* gWindow; 
extern SDL_Renderer* gRenderer;
extern SDL_Texture* gTexture;


extern u32 box_w;
extern u32 box_h;

//static u32 pixels[SCREEN_WIDTH * SCREEN_HEIGHT];
extern u8 map[MAP_ROW * MAP_COL];


//Player State
struct player {
    vec2 pos;
    vec2 dir;

    vec2i mapcord;
};

extern struct player* player;

// Return codes
#define SUCCESS 0
#define ERROR -1

// Raycaster
struct rayhit {
    u8 hit;
    vec2i dist;
    vec2i cord; 
};

extern struct rayhit raycast(float, float);

