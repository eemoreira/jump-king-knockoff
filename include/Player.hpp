#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Entity.hpp"

struct Player : Entity {
    vec2f buffer_held;
    vec2f accel;

    Player(vec2f pos, SDL_Texture* texture, SDL_Rect frame, int scale) :
        Entity(pos, vec2f(0, 0), texture, frame, scale), buffer_held(), accel() {}
    Player() : Entity() {}

    void jump() {
        pos += buffer_held;
    }

    vec2f boost(vec2f to) {
        buffer_held += to;
        return buffer_held;
    }

    void reset_boost() {
        buffer_held = vec2f(0, 0);
    }

    void set_vel(vec2f _vel) {
        vel = _vel;
    }

};
