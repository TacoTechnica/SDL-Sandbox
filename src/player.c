/** player.c
 *
 *      A controllable player
 *
 */
#include "player.h"
#include "game.h"

#include <SDL2/SDL.h>


/** Player_create(x, y)
 *
 *      Creates a new player object but does NOT add it to our game yet.
 *      Use Handler_new_player(x,y)
 */
struct player *Player_create(float x, float y) {
    struct player *player = malloc( sizeof(struct player) );
    player->x = x;
    player->y = y;
    player->rect = malloc( sizeof(SDL_Rect) );
    return player;
}

void Player_update(struct player *player) {
    printf("player x: %f\n", player->x);
    player->x += 0.5;
}

void Player_render(struct player *player) {

    SDL_SetRenderDrawColor(
            Game_renderer,
            255,
            0,
            0,
            255);

    player->rect->x = player->x;
    player->rect->y = player->y;
    player->rect->w = 64;
    player->rect->h = 64;
    SDL_RenderDrawRect(Game_renderer, player->rect);
}
