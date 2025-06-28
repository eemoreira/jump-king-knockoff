#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Segment.hpp"
#include "constants.h"

struct Rectangle {
    std::array<SDL_Vertex, 4> vertex;
    std::array<Segment, 4> segments;
    SDL_Texture* texture;
    vec2f pos;
    float w, h;

    Rectangle(SDL_Texture* _texture, vec2f _pos, float _w, float _h) 
        : texture(_texture), pos(_pos), w(_w), h(_h) {
            SDL_Vertex top_left;
            top_left.position = {pos.x, pos.y};
            top_left.color = {255, 255, 255, 255};
            top_left.tex_coord = {0, 0};


            SDL_Vertex bottom_left;
            bottom_left.position = {pos.x, pos.y + h};
            bottom_left.color = {255, 255, 255, 255};
            bottom_left.tex_coord = {0, 1};

            SDL_Vertex bottom_right;
            bottom_right.position = {pos.x + w, pos.y + h};
            bottom_right.color = {255, 255, 255, 255};
            bottom_right.tex_coord = {1, 1};

            SDL_Vertex top_right;
            top_right.position = {pos.x + w, pos.y};
            top_right.color = {255, 255, 255, 255};
            top_right.tex_coord = {1, 0};

            vertex[0] = top_left;
            vertex[1] = bottom_left;
            vertex[2] = bottom_right;
            vertex[3] = top_right;

            segments[0] = Segment(vec2f(pos.x, pos.y), vec2f(pos.x, pos.y + h), LEFT);
            segments[1] = Segment(vec2f(pos.x, pos.y + h), vec2f(pos.x + w, pos.y + h), DOWN);
            segments[2] = Segment(vec2f(pos.x + w, pos.y + h), vec2f(pos.x + w, pos.y), RIGHT);
            segments[3] = Segment(vec2f(pos.x + w, pos.y), vec2f(pos.x, pos.y), UP);
    }
};

