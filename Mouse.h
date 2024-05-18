#ifndef CYBERDRUNK_MOUSE_H
#define CYBERDRUNK_MOUSE_H

#include <SDL.h>
#include "Game.h"
#include "Window.h"
#include "Camera.h"

class Mouse {
private:
    static int x, y;
    static int screenX, screenY;
    static double gameX, gameY;

public:

    static unsigned int state;
    static void update() {
        state = SDL_GetMouseState(&x, &y);

        screenX = (int)(((double)x / (double)Window::width) * Game::getWidth());
        screenY = (int)(((double)y / (double)Window::height) * Game::getHeight());

        double normMouseX = (double)x / (double)Window::width - 0.5f;
        gameX = (normMouseX * (double)Game::getWidth()) + Camera::x;

        double normMouseY = (-(double)y / (double)Window::height + 0.5f);
        gameY = (normMouseY * (double)Game::getHeight()) + Camera::y;

    }

    static std::pair<int, int> gameToScreen(double gx, double gy) {
        int sx = (gx - Camera::x) + Game::getWidth() / 2;
        int sy = (-gy + Camera::y) + Game::getHeight() / 2;
        return std::make_pair(sx, sy);
    }

    static std::pair<double, double> screenToGame(double sx, double sy) {
        double gx = ((double)sx / Window::width) * Game::getWidth() + Camera::x;
        double gy = ((double)sy / Window::height) * Game::getHeight() + Camera::y;
        return std::make_pair(gx, gy);
    }

    static double getX() {
        return x;
    }

    static double getY() {
        return y;
    }

    static int getScreenX() {
        return screenX;
    }

    static int getScreenY() {
        return screenY;
    }

    static double getGameX() {
        return gameX;
    }

    static double getGameY() {
        return gameY;
    }
};

#endif //CYBERDRUNK_MOUSE_H
