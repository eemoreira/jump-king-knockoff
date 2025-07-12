#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

#include "Entity.hpp"
#include "Map.hpp"
#include "constants.h"

struct RenderWindow {
	SDL_Window* window;
	SDL_Renderer* renderer;

	RenderWindow(const char* title, int W, int H) {
        window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
        if (!window) {
            std::cout << "error creating window" << SDL_GetError() << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    }

    SDL_Texture* loadTexture(const char* path) {
        SDL_Texture* texture = nullptr;

        texture = IMG_LoadTexture(renderer, path);

        if (texture == nullptr) {
            std::cout << "failed to load texture from path " << path << ": " << SDL_GetError() << std::endl;
        }

        return texture;
    }

    void renderEntity(Entity* en) {
        SDL_Rect src, dest;

        src = en->frame;
        const vec2f& pos = en->pos;
        dest.x = pos.x;
        dest.y = pos.y;
        dest.w = en->scale * en->frame.w;
        dest.h = en->scale * en->frame.h;

        SDL_RenderCopy(renderer, en->texture[en->texture_to_display], &src, &dest);
    }
    void renderRectangle(Rectangle* shape) {
        std::array<int, 6> ind = {{0, 1, 2, 0, 2, 3}};
        SDL_RenderGeometry(renderer, shape->texture, (shape->vertex).data(), (shape->vertex).size(), ind.data(), 6); 
    }
    void renderTriangle(Triangle* shape) {
        std::array<int, 3> ind = {{0, 1, 2}};
        SDL_RenderGeometry(renderer, shape->texture, (shape->vertex).data(), (shape->vertex).size(), ind.data(), 3);
    }
    void render(Map& mapa, uint32_t scene) {
        for (auto& en : mapa.ens) {
            renderEntity(en.get());
        }
        for (auto& [block, block_scene] : mapa.blocks) {
            if (block_scene == scene) {
                renderRectangle(block.get());
            }
        }
        for (auto& [triangle, triangle_scene] : mapa.triangles) {
            if (triangle_scene == scene) {
                renderTriangle(triangle.get());
            }
        }
    }
    void setRenderTarget(Rectangle* rect) {
        SDL_SetRenderTarget(renderer, rect->texture);
    }
    void clear() { SDL_RenderClear(renderer); }
    void display() { SDL_RenderPresent(renderer); }
    ~RenderWindow() {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
    }
};
