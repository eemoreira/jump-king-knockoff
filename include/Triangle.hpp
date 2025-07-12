#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Math.hpp"
#include "Segment.hpp"
#include "constants.h"

struct Triangle {
    std::array<SDL_Vertex, 3> vertex;
    std::array<Segment, 3> segments;
    SDL_Texture* texture;

    Triangle(SDL_Texture* _texture, vec2f A, vec2f B, vec2f C) : texture(_texture) {
            SDL_Vertex a;
            a.position = {A.x, A.y};
            a.color = {255, 255, 255, 255};
            a.tex_coord = {0, 0};


            SDL_Vertex b;
            b.position = {B.x, B.y};
            b.color = {255, 255, 255, 255};
            b.tex_coord = {0, 1};

            SDL_Vertex c;
            c.position = {C.x, C.y};
            c.color = {255, 255, 255, 255};
            c.tex_coord = {1, 1};

            vertex[0] = a;
            vertex[1] = b;
            vertex[2] = c;

            segments[0] = Segment(A, B);
            segments[1] = Segment(B, C);
            segments[2] = Segment(C, A);
    }
};

