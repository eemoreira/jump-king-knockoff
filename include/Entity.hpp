#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Rectangle.hpp"
#include "constants.h"

struct Entity {

    vec2f pos, vel;
    SDL_Texture* texture;
    SDL_Rect frame;
    int scale;

    Entity(vec2f _pos, vec2f _vel, SDL_Texture* _texture, SDL_Rect _frame, int _scale) : 
        pos(_pos), vel(_vel), texture(_texture), frame(_frame), scale(_scale) {
    }

    Entity() {}

    virtual void reset_gravity() {}

    virtual Side move_bounded(int BOUND_WIDTH, int BOUND_HEIGHT) { return NONE; }

    virtual vec2f move() {
        pos += vel;
        return pos;
    }


    virtual Side collide_with(Rectangle* oth) { return NONE; }

    virtual Side collide(Entity* oth) { return NONE; }

};
