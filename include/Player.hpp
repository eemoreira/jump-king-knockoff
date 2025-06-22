#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

#include "Entity.hpp"
#include "Rectangle.hpp"

struct Player : Entity {
    vec2f buffer_held;
    vec2f accel;
    bool facing_right;

    Player(vec2f pos, SDL_Texture* texture, SDL_Rect frame, int scale) :
        Entity(pos, vec2f(0, 0), texture, frame, scale), buffer_held(), accel(), facing_right(true) {}
    Player() : Entity() {}

    void jump() {
      // std::cout << "BUFFER HELD = ";
      // buffer_held.print();
        vel += buffer_held;
        vel += facing_right ? vec2f(0.5, 0) : vec2f(-0.5, 0);
        reset_boost();
        accel = vec2f(0, 0.0008); // gravidade :O
    }

    void set_face() {
        if (vel.x > 0) facing_right = true;
        else if (vel.x < 0) facing_right = false;
    }

    vec2f boost(const double bst) {
        //std::cout << "adding to buffer: ";
        //vec2f(0, bst).print();
        buffer_held -= vec2f(0, bst);
        buffer_held.y = std::max(buffer_held.y, -1.0);
        return buffer_held;
    }


    void reset_boost() {
        buffer_held = vec2f(0, 0);
    }

    vec2f move() { 
        pos += vel;
        vel += accel;
        return pos;
    }

    vec2f move_bounded(int BOUND_WIDTH, int BOUND_HEIGHT) override {
        //std::cout << "Player move bounded with vel: ";
        //vel.print();
        //std::cout << "And acceleration: ";
        //accel.print();
        pos += vel;
        vel += accel;
        if (pos.x < 0) pos.x = 0;
        if (pos.x + scale * frame.w > BOUND_WIDTH) pos.x = BOUND_WIDTH - scale * frame.w;
        if (pos.y < 0) pos.y = 0;
        if (pos.y + scale * frame.h > BOUND_HEIGHT) {
            accel = vec2f(0, 0);
            vel = vec2f(0, 0);
            pos.y = BOUND_HEIGHT - scale * frame.h;
        }

        return pos;
    }

    void collide_with(Rectangle* rec) override {
        double left_most = pos.x;
        double right_most = pos.x + scale * frame.w;

        double top_most = pos.y;
        double bottom_most = pos.y + scale * frame.h;

        double rec_left_most = rec->pos.x;
        double rec_right_most = rec->pos.x + rec->w;

        double rec_top_most = rec->pos.y;
        double rec_bottom_most = rec->pos.y + rec->h;

        bool y_intersect = inside(top_most, rec_top_most, rec_bottom_most) ||
                           inside(bottom_most, rec_top_most, rec_bottom_most);

        if (!y_intersect) return;

        if (inside(left_most, rec_left_most, rec_right_most)) {
        std::cout << "trying (" << left_most << ", " << right_most << ") to collide with (" 
            << rec_left_most << ", " << rec_right_most << ")" << std::endl;
            // batendo na parte esquerda do retangulo

            std::cout << "vel before: ";
            vel.print();
            vel = vel.reflect_by(vec2f(0, 1));
            std::cout << std::endl << "vel after: ";
            vel.print();
            std::cout << std::endl;
            return;
        }

        if (inside(right_most, rec_left_most, rec_right_most)) {
        std::cout << "trying (" << left_most << ", " << right_most << ") to collide with (" 
            << rec_left_most << ", " << rec_right_most << ")" << std::endl;
            // batendo na parte esquerda do retangulo

            std::cout << "vel before: ";
            vel.print();
            vel = vel.reflect_by(vec2f(0, -1));
            std::cout << std::endl << "vel after: ";
            vel.print();
            std::cout << std::endl;
            return;
        }
    }

    void set_vel(vec2f _vel) {
        vel = _vel;
    }

};
