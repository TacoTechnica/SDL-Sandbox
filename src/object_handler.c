/** object_handler
 *      
 *      Main object handler: 
 *          Controlls and loops through every object in the game
 *          Lets you add new gameobjects that get added to the loop
 *
 * /

#include "object_handler.h"


// Game Object lists
struct player *ObjectHandler_players;
int ObjectHandler_player_count = 0;

/** ObjectHandler_init()
 *      Initialize every starting object in the game here
 *      as well as any handler variables
 */
void ObjectHandler_init() {

    ObjectHandler_new_player(100,100);

}

/** ObjectHandler_tick()
 *      Ticks all of our objects (called at every frame)
 */
void ObjectHandler_tick() {
    int i = 0;
    // Update all players
    while(i < ObjectHandler_player_count && ObjectHandler_players[i]) {
        struct player current_player = ObjectHandler_players[i];
        Player_update(player);
    }
}

/** ObjectHandler_render()
 *      Renders all of our objects (called at every frame)
 */
void ObjectHandler_render() {
    int i = 0;
    // Render all players
    while(i < ObjectHandler_player_count && ObjectHandler_players[i]) {
        struct player current_player = ObjectHandler_players[i];
        Player_render(player);
    }

}

/** ObjectHandler_new_player(x, y)
 *      Creates a new player object AND adds it to our game.
 *      Use this to make new players
 */
struct player *ObjectHandler_new_player(double x, double y) {
    struct player *player = Player_create(x,y);
    realloc(ObjectHandler_players, sizeof(struct player) * (ObjectHandler_player_count + 1));
    ObjectHandler_players[ObjectHandler_player_count] = &player;

    ObjectHandler_player_count++;

    return player
}
