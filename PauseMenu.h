#ifndef CYBERDRUNK2137_PAUSEMENU_H
#define CYBERDRUNK2137_PAUSEMENU_H

#include "TestObject.h"
#include "Button.h"
#include "ResourceManager.h"
#include <vector>

class PauseMenu: GameObject{
public:

    static std::vector<PauseMenu*> registry;
    PauseMenu(std::string name = "PauseMenu",double x = 0.0,double y = 0.0, SDL_Texture* texture = ResourceManager::loadTexture("pauseSheet.png"),int x_origin = 0,int y_origin = 0,int totalFrames = 1,int numberOfAnimations = 1) : GameObject(std::move(name), x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations) {
    }
    void render() override;
    void setPosition(double x, double y);
    ~PauseMenu() override;
};

#endif //CYBERDRUNK2137_PAUSEMENU_H
