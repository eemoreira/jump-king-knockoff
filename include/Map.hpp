#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "Entity.hpp"
#include "Player.hpp"
#include "Rectangle.hpp"

#include "constants.h"

struct Map {
    std::vector<std::unique_ptr<Entity>> ens;
    std::vector<std::unique_ptr<Rectangle>> blocks;

    void addEntity(std::unique_ptr<Entity> en) {
        ens.emplace_back(std::move(en));
    }
    void addRectangle(std::unique_ptr<Rectangle> rec) {
        blocks.emplace_back(std::move(rec));
    }

    bool inside(double me, double l, double r) {
        return me >= l && me <= r;
    }

    bool check_collision(int i, int j) {
        return ens[i]->collide(ens[j].get());
    }

    void move() {
        for (auto& en : ens) {
            en->move_bounded(WIDTH, HEIGHT);
            for (auto& block : blocks) {
                en->collide_with(block.get());
            }
        }
    }

    void collide() {
        for (int i = 0; i < int(ens.size()); i++) {
            for (int j = 0; j < i; j++) {
                if (check_collision(i, j)) {}
            }
        }
    }

    Map () {}
};
