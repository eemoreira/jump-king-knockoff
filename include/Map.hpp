#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "Entity.hpp"
#include "Player.hpp"
#include "constants.h"

struct Map {
    std::vector<std::unique_ptr<Entity>> ens;

    void add(std::unique_ptr<Entity> en) {
        ens.emplace_back(std::move(en));
    }

    bool inside(double me, double l, double r) {
        return me >= l && me <= r;
    }

    bool check_collision(int i, int j) {
        auto work = [&]() {
            double f_x_rigth = (ens[i]->pos).x + (ens[i]->frame).w * (ens[i]->scale);
            double f_y_down = (ens[i]->pos).y + (ens[i]->frame).h * (ens[i]->scale);

            double g_x_rigth = (ens[j]->pos).x + (ens[j]->frame).w * (ens[j]->scale);
            double g_y_down = (ens[j]->pos).y + (ens[j]->frame).h * (ens[j]->scale);

            double f_x_left = (ens[i]->pos).x;
            double g_x_left = (ens[j]->pos).x;

            double f_y_up = (ens[i]->pos).y;
            double g_y_up = (ens[j]->pos).y;

            bool x_intersect = inside(f_x_left, g_x_left, g_x_rigth) || inside(f_x_rigth, g_x_left, g_x_rigth);
            bool y_intersect = inside(f_y_up, g_y_up, g_y_down) || inside(f_y_down, g_y_up, g_y_down);

            if (x_intersect && y_intersect) {
                ens[i]->flip_velocity();
                ens[j]->flip_velocity();
                return true;
            }
            return false;
        };

        if (work()) return true;
        std::swap(i, j);
        if (work()) return true;

        return false;
    }

    void move() {
        for (auto& en : ens) {
            en->move_bounded(WIDTH, HEIGHT);
        }
        collide();
    }

    void collide() {
        for (int i = 0; i < int(ens.size()); i++) {
            for (int j = i + 1; j < int(ens.size()); j++) { 
                
                if (check_collision(i, j)) { 
                
                } 
            }
        }
    }

    Map () {}
};
