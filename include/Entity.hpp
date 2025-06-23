#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include <iostream>

#include "Math.hpp"
#include "Rectangle.hpp"

struct Entity {

    vec2f pos, vel;
    SDL_Texture* texture;
    SDL_Rect frame;
    int scale;

    Entity(vec2f _pos, vec2f _vel, SDL_Texture* _texture, SDL_Rect _frame, int _scale) : 
        pos(_pos), vel(_vel), texture(_texture), frame(_frame), scale(_scale) {
    }

    Entity() {}

    void flip_velocity() {
        vel *= -1;
    }

    virtual vec2f move_bounded(int BOUND_WIDTH, int BOUND_HEIGHT) {
        pos += vel;
        bool col = false;
        if (pos.x < 0) pos.x = 0, col = true;
        if (pos.x + scale * frame.w > BOUND_WIDTH) pos.x = BOUND_WIDTH - scale * frame.w, col = true;
        if (pos.y < 0) pos.y = 0, col = true;
        if (pos.y + scale * frame.h > BOUND_HEIGHT) pos.y = BOUND_HEIGHT - scale * frame.h, col = true;

        if (col) flip_velocity();

        return pos;
    }

    virtual vec2f move() {
        pos += vel;
        return pos;
    }


    virtual void collide_with(Rectangle* oth) {}

    virtual bool collide(Entity* oth) {
        double f_x_right = (pos).x + (frame).w * (scale);
        double f_y_down = (pos).y + (frame).h * (scale);

        double g_x_right = (oth->pos).x + (oth->frame).w * (oth->scale);
        double g_y_down = (oth->pos).y + (oth->frame).h * (oth->scale);

        double f_x_left = (pos).x;
        double g_x_left = (oth->pos).x;

        double f_y_up = (pos).y;
        double g_y_up = (oth->pos).y;

        bool x_intersect = inside(f_x_left, g_x_left, g_x_right) || inside(f_x_right, g_x_left, g_x_right);
        bool y_intersect = inside(f_y_up, g_y_up, g_y_down) || inside(f_y_down, g_y_up, g_y_down);

        if (x_intersect && y_intersect) {
            bool col = false;
            if (inside(f_x_left, g_x_left, g_x_right)) {
                pos.x = g_x_right;
                col = true;
            }
            if (inside(f_x_right, g_x_left, g_x_right)) {
                pos.x = g_x_left - frame.w * scale;
                col = true;
            }
            if (inside(f_y_up, g_y_up, g_y_down)) {
                pos.y = g_y_down;
                col = true;
            }
            if (inside(f_y_down, g_y_up, g_y_down)) {
                pos.y = g_y_up - frame.h * scale;
                col = true;
            }

            if (col) flip_velocity();

            return true;
        }

        return false;
    }

};
