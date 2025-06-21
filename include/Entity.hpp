#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Math.hpp"

struct Entity {

    vec2f pos;
    SDL_Texture* texture;
    SDL_Rect frame;
    int scale;

    Entity(vec2f _pos, SDL_Texture* _texture, SDL_Rect _frame, int _scale): pos(_pos), texture(_texture), frame(_frame), scale(_scale) {
    }

    vec2f getPos() { return pos; }
    SDL_Rect getFrame() { return frame; }
    SDL_Texture* getTexture() { return texture; }

    vec2f move_bounded(vec2f to, int BOUND_WIDTH, int BOUND_HEIGHT) {
        pos += to;
        pos.print();
        if (pos.x < 0) pos.x = 0;
        if (pos.x + scale * frame.w > BOUND_WIDTH) pos.x = BOUND_WIDTH - scale * frame.w;
        if (pos.y < 0) pos.y = 0;
        if (pos.y + scale * frame.h > BOUND_HEIGHT) pos.y = BOUND_HEIGHT - scale * frame.h;
        return pos;
    }

    vec2f move(vec2f to) {
        pos += to;
        return pos;
    }

};
