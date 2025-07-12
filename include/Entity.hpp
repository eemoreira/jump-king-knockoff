#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Rectangle.hpp"
#include "constants.h"

struct Entity {

    vec2f pos, vel;
    std::vector<SDL_Texture*> texture;
    SDL_Rect frame;
    int scale;
    size_t texture_to_display;

    Entity(vec2f _pos, vec2f _vel, std::vector<SDL_Texture*> _texture, SDL_Rect _frame, int _scale) : 
        pos(_pos), vel(_vel), texture(_texture), frame(_frame), scale(_scale), texture_to_display(0) {
    }

    Entity() {}

    virtual void reset_gravity() {}
    virtual void setTextureToDisplay(size_t to) {}

    virtual Side move_bounded(int BOUND_WIDTH, int BOUND_HEIGHT) { return NONE; }

    virtual void move() {
        pos += vel;
    }


    virtual Side collide_with(Rectangle* oth) { return NONE; }

    virtual Side collide(Entity* oth) { return NONE; }

};
