#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Math.hpp"

struct Entity {

    vec2f pos, vel;
    SDL_Texture* texture;
    SDL_Rect frame;
    int scale;

    Entity(vec2f _pos, vec2f _vel, SDL_Texture* _texture, SDL_Rect _frame, int _scale) : 
        pos(_pos), vel(_vel), texture(_texture), frame(_frame), scale(_scale) {
    }

    Entity() {}

    vec2f getPos() { return pos; }
    SDL_Rect getFrame() { return frame; }
    SDL_Texture* getTexture() { return texture; }

    void flip_velocity() {
        vel *= -1;
    }

    vec2f move_bounded(int BOUND_WIDTH, int BOUND_HEIGHT) {
        pos += vel;
        bool col = false;
        if (pos.x < 0) pos.x = 0, col = true;
        if (pos.x + scale * frame.w > BOUND_WIDTH) pos.x = BOUND_WIDTH - scale * frame.w, col = true;
        if (pos.y < 0) pos.y = 0, col = true;
        if (pos.y + scale * frame.h > BOUND_HEIGHT) pos.y = BOUND_HEIGHT - scale * frame.h, col = true;

        if (col) vel *= -1;

        return pos;
    }

    vec2f move() {
        pos += vel;
        return pos;
    }

};
