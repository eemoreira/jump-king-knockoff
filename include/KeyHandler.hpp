#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_keyboard.h>
#include <vector>

struct KeyHandler {
    SDL_KeyboardEvent Keys[1 << 9];
    bool held[1 << 9];

    void update_key(SDL_KeyboardEvent ken) {
        SDL_Scancode code = ken.keysym.scancode;
        Keys[code] = ken;
        if (Keys[code].state == SDL_RELEASED) held[code] = false;
        if (Keys[code].state == SDL_PRESSED) held[code] = true;
    }


    bool is_pressed(SDL_Scancode code, uint64_t current_time, uint64_t tolerance) {
        return held[code] || (Keys[code].state == SDL_PRESSED && current_time - Keys[code].timestamp <= tolerance);
    }

    bool is_released(SDL_Scancode code, uint64_t current_time, uint64_t tolerance) {
        return Keys[code].state == SDL_RELEASED && current_time - Keys[code].timestamp <= tolerance;
    }

    KeyHandler() { 
        memset(Keys, 0, sizeof Keys);
        memset(held, 0, sizeof held);
    }
};
