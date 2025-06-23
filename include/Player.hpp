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
        vel += facing_right ? vec2f(0.05, 0) : vec2f(-0.05, 0);
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
        if (pos.x < 0) {
            //pos.x = 0;
            vel = vel.reflect_by(vec2f(1, 0));
        }
        if (pos.x + scale * frame.w > BOUND_WIDTH) {
            //pos.x = BOUND_WIDTH - scale * frame.w;
            vel = vel.reflect_by(vec2f(-1, 0));
        }
        if (pos.y < 0) {
            //pos.y = 0;
            vel = vel.reflect_by(vec2f(0, 1));
        }
        if (pos.y + scale * frame.h > BOUND_HEIGHT) {
            accel = vec2f(0, 0);
            vel = vec2f(0, 0);
            pos.y = BOUND_HEIGHT - scale * frame.h;
        }

        return pos;
    }

    bool bounding_box_inter(Rectangle* rec) {
        double f_x_right = (pos).x + (frame).w * (scale);
        double f_y_down = (pos).y + (frame).h * (scale);

        double g_x_right = (rec->pos).x + (rec)->w;
        double g_y_down = (rec->pos).y + (rec)->h;

        double f_x_left = (pos).x;
        double g_x_left = (rec->pos).x;

        double f_y_up = (pos).y;
        double g_y_up = (rec->pos).y;

        bool x_intersect = inside(f_x_left, g_x_left, g_x_right) || inside(f_x_right, g_x_left, g_x_right);
        bool y_intersect = inside(f_y_up, g_y_up, g_y_down) || inside(f_y_down, g_y_up, g_y_down);

        return x_intersect && y_intersect;
    }

    void collide_with(Rectangle* rec) override {
        if (!bounding_box_inter(rec)) return;
        auto& segs = rec->segments; 
        vec2f center(vec2f(pos.x + frame.w/2, pos.y + frame.h/2));
        double dist = (pos - center).norm();
        Segment my_segment(center, center + vel.unity() * dist);
        for (auto& se : segs) {
            auto [has_intersection, inter] = my_segment.intersect(se);
            if (has_intersection) {
                vec2f normal = se.normal();
                std::cout << "INTERSECT segment :";
                se.p.print();
                std::cout << ", ";
                se.q.print();
                std::cout << ",";
                std::cout << " NORMAL: ";
                normal.print();
                std::cout << std::endl;
                vel = vel.reflect_by(normal);
                //vel = vec2f(0, 0);
                return;
            }
        }
    }

    void set_vel(vec2f _vel) {
        vel = _vel;
    }

};
