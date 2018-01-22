#include <SDL2/SDL.h>

struct player {
    float x; float y; float angle;
    float vel_x; float vel_y;
    float vel_angle;
    SDL_Rect *rect;
};

struct player *Player_create(float x, float y);
void Player_update(struct player *player);
void Player_render(struct player *player);
