#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_keyboard.h>
#include <vector>

struct KeyHandler {
    SDL_KeyboardEvent Keys[1 << 9];

    void update_key(SDL_KeyboardEvent ken) {
        Keys[ken.keysym.scancode] = ken;
    }

    bool is_pressed(SDL_Scancode code, uint64_t current_time, uint64_t tolerance) {
        return Keys[code].state == SDL_PRESSED && current_time - Keys[code].timestamp <= tolerance;
    }

    bool is_released(SDL_Scancode code, uint64_t current_time, uint64_t tolerance) {
        return Keys[code].state == SDL_RELEASED && current_time - Keys[code].timestamp <= tolerance;
    }

    KeyHandler() { 
        memset(Keys, 0, sizeof Keys);
    }
};
