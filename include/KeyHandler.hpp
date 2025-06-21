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

    bool is_pressed(SDL_Scancode code) {
        return Keys[code].state == SDL_PRESSED;
    }

    bool is_released(SDL_Scancode code) {
        return Keys[code].state == SDL_RELEASED;
    }

    std::vector<SDL_KeyboardEvent> get_key_events(uint64_t current_time, uint64_t tolerance) {
        std::vector<SDL_KeyboardEvent> events;

        for (int i = 0; i < 1 << 9; i++) {
            if (current_time - Keys[i].timestamp > tolerance) continue;
            events.emplace_back(Keys[i]);
        }

        return events;
    }

    KeyHandler() { 
        memset(Keys, 0, sizeof Keys);
    }
};
