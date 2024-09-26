#include <SDL2/SDL.h> 
// Engine header

extern int init(void);

extern int loadMedia(const char*);

extern void closeWindow(void);

extern int eventInit(void);

extern int eventLoop(void);

//Global variables
extern SDL_Window* gWindow; 
extern SDL_Surface* gSurface;
extern SDL_Renderer* gRenderer;

// Return codes
#define SUCCESS 0
#define ERROR -1
