#ifndef CYBERDRUNK2137_BUTTON_H
#define CYBERDRUNK2137_BUTTON_H

#include "TestObject.h"


class Button:GameObject{
public:
    bool onClick();
    static std::vector<Button*> registry;
    Button(std::string name = "Pause Menu", double x = 0.0, double y = 0.0, SDL_Texture* texture = nullptr, int x_origin = 0, int y_origin = 0, int totalFrames = 1, int numberOfAnimations = 1);
    double getX() const;
    double getY() const;
    double getWidth();
    double getHeight();
    ~Button() override;
    void setPosition(double x, double y);
    void render() override;
};




#endif //CYBERDRUNK2137_BUTTON_H
