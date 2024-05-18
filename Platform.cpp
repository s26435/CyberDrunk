#include "Platform.h"
#include "Game.h"
#include "Camera.h"

std::vector<Platform *> Platform::registry;

void Platform::render() {
    GameObject::render();
    if(this->collider != nullptr)
    {
        if (true)
        {
            SDL_SetRenderDrawColor(Game::getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
        } else {
            SDL_SetRenderDrawColor(Game::getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
        }

        SDL_Rect destRect = {
                static_cast<int>(-Camera::x + x_pos) - x_origin + Game::getWidth() / 2,
                static_cast<int>(Camera::y - y_pos) - y_origin + Game::getHeight() / 2,
                static_cast<int>(width),
                static_cast<int>(height)
        };
        SDL_RenderDrawRect(Game::getRenderer(), &destRect);
    }
}

Platform::~Platform() {
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

double Platform::getY(){
    return this->y_pos;
}

double Platform::getX() {
    return this->x_pos;
}

void Platform::setY(double y) {
    GameObject::setY(y);
}
void Platform::setX(double x) {
    GameObject::setX(x);
}

double Platform::getWidth() {
    return GameObject::getWidth();
}

double Platform::getHeight() {
    return GameObject::getHeight();
}

void Platform::update(double deltaTime) {
    GameObject::update(deltaTime);
    if (collider != nullptr)
    {
        collider->x = x_pos - x_origin;
        collider->y = y_pos;
        collider->width = width;
        collider->height = height;;
    }
    deltaTime *= timeMultiplier;

}

CollisionResult Platform::checkCollisionWith(const TestObject& other) const {
    return collider->checkCollision(*other.collider);
}


