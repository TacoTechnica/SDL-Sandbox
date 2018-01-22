/** game.c
 *     The main game file, containing main and the central game loop
 */

#include<stdio.h>
#include<SDL2/SDL.h>


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define GAME_TITLE "C-Astro Party"

#define GAME_FPS 60

void Game_start();
void Game_sdl_init();
void Game_loop();
void Game_tick();
void Game_render();
void Game_stop();

SDL_Window *Game_window;
SDL_Renderer *Game_renderer;
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
    printf("tick!\n");

    // Handle SDL Events (keyboard input and window closing)
    while (SDL_PollEvent(&Game_event)) {
        switch(event.type) {
            // Grab window events
            case SDL_WINDOWEVENT:
                switch (event.window.event):
                    case SDL_WINDOWEVENT_CLOSE:
                        Game_stop();
                        exit(0);
                    break;
                break;
            case SDL_KEYDOWN:
                InputHandler_press_key(event.key.keysym.sym);
                break;
            case SDL_KEYUP:
                InputHandler_release_key(event.key.keysym.sym);
                break;
                
    }

    InputHandler_tick();

    InputHandler_update(); 

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
