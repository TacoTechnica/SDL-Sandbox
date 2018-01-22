/** game.c
 *     The main game file, containing main and the central game loop
 */

#include "game.h"
#include "object_handler.h"
#include "input_handler.h"

#include<stdio.h>
#include<SDL2/SDL.h>


void Game_start();
void Game_sdl_init();
void Game_loop();
void Game_tick();
void Game_render();

int Game_running = 0;
SDL_Event Game_sdl_event;

/* void Game_sdl_init()
 *  Init sdl elements (window and renderer)
 */
void Game_sdl_init() {

    if (SDL_Init( SDL_INIT_EVERYTHING ) != 0) {
        printf("SDL Init failed! You're kinda screwed now\n");
        exit(1);
    }

    Game_window = SDL_CreateWindow(
            GAME_TITLE,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            SDL_WINDOW_OPENGL//SDL_WINDOW_BORDERLESS//0 //SDL_WINDOW_INPUT_GRABBED
            );
    if (Game_window == NULL) {
        printf("SDL Window failed to create. Have fun\n");
        exit(1);
    }

    Game_renderer = SDL_CreateRenderer(
            Game_window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
            );
    if (Game_renderer == NULL) {
        SDL_DestroyWindow(Game_window);
        printf("SDL Renderer failed to create. Good luck working with an empty window\n");
        SDL_Quit();
        exit(1);
    }
}

/* void Game_start()
 *  Starts the game: Initializes everything, then runs the main loop
 */
void Game_start() {
    Game_sdl_init();
    Game_running = 1;

    ObjectHandler_init();

    Game_loop();
}

/* void Game_loop()
 *  Main Game loop, calling every other loop
 */

void Game_loop() {
    unsigned int now_time;
    unsigned int prev_time = SDL_GetTicks();
    unsigned int delta_time;

    int should_render = 0;

    unsigned int ms_per_frame = 1000 / GAME_FPS;

    int tick_count = 0;

    while(Game_running) {
        should_render = 0;

        now_time = SDL_GetTicks();

        delta_time = now_time - prev_time;
        while(delta_time > ms_per_frame) {
            delta_time -= ms_per_frame;
            should_render = 1;

            Game_tick();
            tick_count++;

            prev_time = now_time;
        }

        if (should_render) {
            Game_render();
        }

        // Quit after 4 seconds
        if (tick_count > GAME_FPS * 4) {
            Game_stop();
            exit(0);
        }

    }
}

void Game_tick() {

    // Handle SDL Events (keyboard input and window closing)
    while (SDL_PollEvent(&Game_sdl_event)) {
        switch(Game_sdl_event.type) {
            // Grab window events
            case SDL_WINDOWEVENT:
                switch (Game_sdl_event.window.event) {
                    case SDL_WINDOWEVENT_CLOSE:
                        Game_stop();
                        exit(0);
                    break;
                }
                break;
            case SDL_KEYDOWN:
                InputHandler_press_key(Game_sdl_event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                InputHandler_release_key(Game_sdl_event.key.keysym.sym);
                break;
        } 
    }


    ObjectHandler_tick();

    // InputHandler_tick() MUST be called after the object tick
    InputHandler_tick(); 
    
}

void Game_render() {
    SDL_SetRenderDrawColor(
            Game_renderer,
            0,
            0,
            0,
            255);
    SDL_RenderClear(Game_renderer);

    ObjectHandler_render();

    SDL_RenderPresent(Game_renderer);
}

void Game_stop() {
    Game_running = 0;
    SDL_DestroyRenderer(Game_renderer);
    SDL_DestroyWindow(Game_window);
    SDL_Quit();
}


int main() {

    printf("Starting game\n");

    Game_start();
    Game_stop();
    return 0;
}
