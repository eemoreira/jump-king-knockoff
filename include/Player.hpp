#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include <cassert>

#include "Entity.hpp"
#include "Rectangle.hpp"
#include "constants.h"
#include "Segment.hpp"

struct Player : Entity {
    vec2f buffer_held;
    vec2f accel;
    bool facing_right;
    bool grounded;
    Segment on_top;
    uint32_t scene;
    uint64_t time_factor;

    Player(vec2f pos, std::vector<SDL_Texture*> texture, SDL_Rect frame, int scale) :
        Entity(pos, 
               vec2f(0, 0), 
               texture,
               frame,
               scale),
               buffer_held(),
               accel(),
               facing_right(true),
               scene(0),
               time_factor(1)
        {
            make_grounded(Segment(GROUND_LEFT_BOUND, GROUND_RIGHT_BOUND, DOWN));
        }

    Player() : Entity() {}

    void jump() {
        if (!grounded) return;
        //std::cout << "BUFFER HELD = " << buffer_held << std::endl;
        vel += buffer_held;
        vel.x = facing_right ? PLAYER_X_VELOCITY : -PLAYER_X_VELOCITY;
        reset_boost();
        reset_gravity();
        grounded = false;
    }

    void make_grounded(Segment se) {
        //std::cout << "GROUNDED" << std::endl;
        if (!grounded) {
            reset_movement();
            reset_boost();
        }
        grounded = true;
        on_top = se;
    }

    void set_face() {
        if (vel.x > 0) {
            facing_right = true;
            if (texture_to_display & 1) texture_to_display ^= 1;
        }
        else if (vel.x < 0) {
            facing_right = false;
            texture_to_display = 1;
            if (~texture_to_display & 1) texture_to_display ^= 1;
        }
    }

    vec2f boost() {
        if (buffer_held.isZero()) {
            buffer_held = vec2f(0, -INITIAL_BOOST);
        } else {
            buffer_held -= vec2f(0, BOOST);
            buffer_held.y = std::max(buffer_held.y, -MAX_JUMPING_BUFFER);
        }

        texture_to_display |= 2;
        return buffer_held;
    }

    void reset_boost() {
        buffer_held = vec2f(0, 0);
        if (texture_to_display & 2) texture_to_display ^= 2;
    }

    void reset_movement() {
        vel = accel = vec2f(0, 0);
        if (texture_to_display & 2) texture_to_display ^= 2;
        //std::cout << "RESETING MOVEMENT" << std::endl;
    }

    void reset_gravity() override {
        if (!grounded) {
            //std::cout << "GRAVITY WORKING" << std::endl;
            accel = vec2f(0, GRAVITY);
        } else {
            //std::cout << "GRAVITY NOT WORKING" << std::endl;
            accel = vec2f(0, 0);
        }
    }

    vec2f move() { 
        //std::cout << "MOVING WITH VEL = " << vel << ", AND TIME FACTOR = " << time_factor << std::endl;
        pos += vel * time_factor;
        vel += accel;
        if (pos.x < on_top.left_most() - 1 || pos.x > on_top.right_most() + 1) {
            grounded = false;
        }

        if (!(vel.isZero() && accel.isZero())) {
            reset_boost();
        }

        return pos;
    }

    Side move_bounded(int BOUND_WIDTH, int BOUND_HEIGHT) override {
        //std::cout << "Player move bounded with vel: ";
        //std::cout << "And acceleration: ";
        move();
        Side ret = NONE;
        if (pos.x < 0) {
            vel.x = 0;
            pos.x = 0;
            //std::cout << "LEFT WALL with vel = " << vel << std::endl;
            ret = LEFT;
        }

        if (pos.x + scale * frame.w > BOUND_WIDTH) {
            vel.x = 0;
            pos.x = BOUND_WIDTH - scale * frame.w;
            //std::cout << "RIGHT WALL with vel = " << vel << std::endl;
            ret = RIGHT;
        }

        if (pos.y < 0) {
            ret = UP;
            scene++;
            pos.y = BOUND_HEIGHT;
            std::cout << "GOING TO NEXT SCENE = " << scene << std::endl;
            return UP;
        }

        if (scene == 0 && pos.y + scale * frame.h > BOUND_HEIGHT) {
            vel.y = 0;
            make_grounded(Segment(GROUND_LEFT_BOUND, GROUND_RIGHT_BOUND, DOWN));
            ret = DOWN;
           // std::cout << "GROUNDED ON FLOOR " << GROUND_LEFT_BOUND << ", " << GROUND_RIGHT_BOUND 
           //     << ", vel = " << vel << " accell = " << accel << std::endl;
        }
        if (scene > 0 && pos.y > BOUND_HEIGHT) {
            std::cout << "GOING DOWN ONE SCENE" << std::endl;
            scene--;
            pos.y = 0;
            ret = DOWN;
        }


        return ret;
    }

    bool bounding_box_inter(Rectangle* rec) {
        float f_x_right = (pos).x + (frame).w * (scale);
        float f_y_down = (pos).y + (frame).h * (scale);

        float g_x_right = (rec->pos).x + (rec)->w;
        float g_y_down = (rec->pos).y + (rec)->h;

        float f_x_left = (pos).x;
        float g_x_left = (rec->pos).x;

        float f_y_up = (pos).y;
        float g_y_up = (rec->pos).y;
        bool x_intersect = inside(f_x_left, g_x_left, g_x_right) || inside(f_x_right, g_x_left, g_x_right);
        bool y_intersect = inside(f_y_up, g_y_up, g_y_down) || inside(f_y_down, g_y_up, g_y_down);

        return x_intersect && y_intersect;
    }

    Side collide_with(Rectangle* rec) override {
        if (!bounding_box_inter(rec)) return NONE;
        auto& segs = rec->segments; 
        vec2f center(vec2f(pos.x + frame.w/2, pos.y + frame.h/2));
        float dist = 4 * (pos - center).norm();
        Segment my_segment(center, center + vel.unity() * dist, NONE);
        for (auto& se : segs) {
            auto [has_intersection, inter] = my_segment.intersect(se);
            if (has_intersection) {
                vec2f normal = se.normal();
                std::cout << "INTERSECT segment :" << se.p << ", " << se.q << ", NORMAL: " << normal << std::endl;
                if (se.side == UP) {
                    std::cout << "RESETING" << std::endl; 
                    pos.y = se.p.y - scale * frame.h;
                    make_grounded(se);
                    reset_movement();
                } else {
                    vel = vel.reflect_by(normal);
                }
                return se.side;
            }
        }
        return NONE;
    }

    void setTextureToDisplay(size_t to) override {
        texture_to_display = to;
    }

    void set_vel(vec2f _vel) {
        vel = _vel;
    }

};
