#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<string>

#include "Surface.hpp"

Surface::Surface(const std::string name) : surface(nullptr) {
    const std::string path = std::string("res/") + name;
    surface = SDL_LoadBMP(path.c_str());
    if (!surface) {
        std::cout << "FILE " << path << " NOT FOUND" << std::endl;
    }
}

Surface::Surface(SDL_Window* window) : surface(nullptr) {
    surface = SDL_GetWindowSurface(window);
}

bool Surface::apply_from(Surface& oth) {
    return SDL_BlitSurface(oth.getSurface(), nullptr, surface, nullptr) == 0;
}

SDL_Surface* Surface::getSurface() {
    return surface;
}

Surface::~Surface() {
    SDL_FreeSurface(surface);
}

