#include <iostream>
#include "Button.h"
#include "ResourceManager.h"

std::vector<Button *> Button::registry;

Button::Button(std::string name, double x, double y, SDL_Texture *texture, int x_origin, int y_origin, int totalFrames,
               int numberOfAnimations) : GameObject(name, x, y, texture, x_origin, y_origin, totalFrames,
                                                    numberOfAnimations) {
}


void Button::setPosition(double x, double y) {
    this->y_pos = y;
    this->x_pos = x;
}

double Button::getX() const {
    return this->x_pos;
}
double Button::getY() const {
    return GameObject::getY();
}
bool Button::onClick(){
    if(this->name == "resumeButton"){
        return true;
    }
    else if(this->name == "exitButton"){
        return false;
    }
    else return false;
}

Button::~Button() {
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

void Button::render() {
        GameObject::render();
}

double Button::getWidth() {
    return this->width;
}

double Button::getHeight() {
    return this->height;
}





