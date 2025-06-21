#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#include "Entity.hpp"

struct RenderWindow {
	SDL_Window* window;
	SDL_Renderer* renderer;

	RenderWindow(const char* title, int W, int H) {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cout << "error creating window" << SDL_GetError() << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    }
    SDL_Texture* loadTexture(const char* path) {
        SDL_Texture* texture = nullptr;

        texture = IMG_LoadTexture(renderer, path);

        if (texture == nullptr) {
            std::cout << "failed to load texture from path " << path << ": " << SDL_GetError() << std::endl;
        }

        return texture;
    }
    void render(Entity& en) {
        SDL_Rect src, dest;

        src = en.getFrame();
        const vec2f& pos = en.getPos();
        dest.x = pos.x;
        dest.y = pos.y;
        dest.w = en.getFrame().w;
        dest.h = en.getFrame().h;

        SDL_RenderCopy(renderer, en.getTexture(), &src, &dest);
    }
    void clear() { SDL_RenderClear(renderer); }
    void display() { SDL_RenderPresent(renderer); }
    ~RenderWindow() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
};
