/** player.c
 *
 *      A controllable player
 *
 */
#include "player.h"
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
    return player;
}

void Player_update(struct player player) {
    player.x += 0.5;
}

void Player_render(struct player player) {

    SDL_SetRenderDrawColor(
            renderer,
            255,
            0,
            0,
            255);

    SDL_Rect player_rect;
    player_rect.x = player.x;
    player_rect.y = player.y;
    player_rect.w = 64;
    player_rect.h = 64;
    SDL_RenderDrawRect(renderer, player_rect);
}
