#include<SDL2/SDL.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GAME_TITLE "C-Astro Party"

#define GAME_FPS 60

SDL_Window *Game_window;
SDL_Renderer *Game_renderer;

void Game_stop();
