#include "Window.h"
#include <iostream>

const char* Window::title;
int Window::width;
int Window::height;
SDL_Window* Window::window = nullptr;

bool Window::initialize(const char* t) {
    title = t;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_DisplayMode current;
    if (SDL_GetCurrentDisplayMode(0, &current) != 0) {
        return false;
    }

    float aspect_ratio = (float)current.w / (float)current.h;
    width = current.w;
    height = current.h;

    // Ustawiamy okno na pełny ekran z "wirtualną" rozdzielczością 200x96
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_FULLSCREEN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Window::cleanUp() {
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }

    SDL_Quit();
}

SDL_Window* Window::getWindow() {
    return window;
}