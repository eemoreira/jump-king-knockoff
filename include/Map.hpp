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
#include "Segment.hpp"

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

    bool inside(float me, float l, float r) {
        return me >= l && me <= r;
    }

    bool check_collision(int i, int j) {
        return ens[i]->collide(ens[j].get());
    }

    void move() {
        for (auto& en : ens) {
            bool col = false;

            // hit ground
            col |= en->move_bounded(WIDTH, HEIGHT) == DOWN;

            for (auto& block : blocks) {
                // on top of a block
                col |= en->collide_with(block.get()) == UP;
            }


            if (!col) {
                en->reset_gravity();
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
