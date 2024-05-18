#include <SDL.h>
#include "Window.h"
#include "Game.h"

int main(int argc, char* argv[])
{
    Window::initialize("Cyberdrunk2137");
    Game::initialize();

    Game::loop();
    Game::cleanUp();
    Window::cleanUp();
    return 0;
}