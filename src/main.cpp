#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <array>
#include <vector>

#include "RenderWindow.hpp"
#include "Entity.hpp" 
#include "constants.h"


int main(int argv, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0) {
		std::cout << "ERROR ON SDL_INIT: " << SDL_GetError() << std::endl; 
		return 1;
	}
	if (!IMG_Init(IMG_INIT_PNG)) {
		std::cout << "ERROR ON IMG_INIT: " << IMG_GetError() << std::endl; 
		return 1;
	}

    RenderWindow win("RPG - hehe", WIDTH, HEIGHT);
    SDL_Texture* grass = win.loadTexture("res/gfx/ground_grass_1.png");
    SDL_Texture* plat = win.loadTexture("res/gfx/brackeys_platformer_assets/sprites/platforms.png");
    std::vector<Entity> grass_blocks;

    SDL_Rect grass_rect;
    grass_rect.x = grass_rect.y = 0;
    grass_rect.w = grass_rect.h = 32;

    for (int i = 0; i < FLOOR_SIZE; i++) {
        grass_blocks.emplace_back(vec2f(32 * i, HEIGHT - 32), grass, grass_rect, 1);
    }

    std::vector<Entity> platforms;
    SDL_Rect plat_rect;
    plat_rect.x = plat_rect.y = 0;
    plat_rect.w = 16;
    plat_rect.h = 8;
    for (int i = 1; i <= 5; i++) {
        platforms.emplace_back(vec2f(0, HEIGHT - 100 * i), plat, plat_rect, 3);
    }

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        win.clear();
        for (auto& block : grass_blocks) {
            win.render(block);
        }
        for (auto &block : platforms) {
            block.move_bounded(vec2f(0.1, 0), WIDTH, HEIGHT);
            win.render(block);
        }
        win.display();
    }


    SDL_Quit();
	return 0;
}
