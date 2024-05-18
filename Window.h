#ifndef UNTITLED_WINDOW_H
#define UNTITLED_WINDOW_H


#include <SDL.h>

class Window {
public:
    static bool initialize(const char* title);
    static void cleanUp();
    static SDL_Window* getWindow();

    static int width;
    static int height;

private:
    static const char* title;
    static SDL_Window* window;
};

#endif //UNTITLED_WINDOW_H
