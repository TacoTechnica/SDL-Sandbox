/** input_handler
 *
 *      Handles our input.
 *      Use InputHandler_is_key_held, is_key_pressed, and is_key_released 
 *      to check for keyboard inputs
 *
 */

#include "handler.h"
#include<SDL2/SDL.h>

// Whether we're pressing the key currently
bool InputHandler_key_accelerate = 0;
bool InputHandler_key_turn_left = 0;
bool InputHandler_key_shoot = 0;

// Previous keys (so we can tell whether we just pressed a key)
bool InputHandler_key_accelerate_prev = 0;
bool InputHandler_key_turn_left_prev = 0;
bool InputHandler_key_shoot_prev = 0;

/** InputHandler_press_key( key )
 *      Sets a key to true, so that we can say it's being held
 *
 */
void InputHandler_press_key(SDL_Keycode key) {
    switch (key) {
        case INPUT_KEY_ACCELERATE:
            InputHandler_key_accelerate = 1;
            break;
        case INPUT_KEY_TURN:
            InputHandler_key_turn_left = 1;
            break;
        case INPUT_KEY_SHOOT:
            InputHandler_key_shoot = 1;
            break;
    }
}

/** InputHandler_release_key( key )
 *      Sets a key to false, so that we can say it's NOT being held
 *
 */
void InputHandler_release_key(SDL_Keycode key) {
    switch (key) {
        case INPUT_KEY_ACCELERATE:
            InputHandler_key_accelerate = 0;
            break;
        case INPUT_KEY_TURN:
            InputHandler_key_turn_left = 0;
            break;
        case INPUT_KEY_SHOOT:
            InputHandler_key_shoot = 0;
            break;
    }
}

/** InputHandler_update()
 *      Update (tick) for input. Called once per frame, at the END of every frame.
 *      Sets our previous inputs so that we can detect 
 *      what our previous inputs were.
 */
void InputHandler_update() {
    InputHandler_key_accelerate_prev = InputHandler_key_accelerate;
    InputHandler_key_turn_left_prev = InputHandler_key_turn_left;
    InputHandler_key_shoot_prev = InputHandler_key_shoot;
}


bool InputHandler_is_key_held(SDL_Keycode key) {
    switch (key) {
        case INPUT_KEY_ACCELERATE:
            return InputHandler_key_accelerate;
        case INPUT_KEY_TURN:
            return InputHandler_key_turn_left;
        case INPUT_KEY_SHOOT:
            return InputHandler_key_shoot;
    }
}

bool InputHandler_is_key_pressed(SDL_Keycode key) {
    switch (key) {
        case INPUT_KEY_ACCELERATE:
            return InputHandler_key_accelerate && !InputHandler_key_accelerate_prev;
        case INPUT_KEY_TURN:
            return InputHandler_key_turn_left && !InputHandler_key_turn_left;
        case INPUT_KEY_SHOOT:
            return InputHandler_key_shoot && !InputHandler_key_shoot;
    }
}

bool InputHandler_is_key_released(SDL_Keycode key) {
    switch (key) {
        case INPUT_KEY_ACCELERATE:
            return !InputHandler_key_accelerate && InputHandler_key_accelerate_prev;
        case INPUT_KEY_TURN:
            return !InputHandler_key_turn_left && InputHandler_key_turn_left;
        case INPUT_KEY_SHOOT:
            return !InputHandler_key_shoot && InputHandler_key_shoot;
    }

}
