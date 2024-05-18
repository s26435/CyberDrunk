#include "GameObject.h"
#include "Game.h"
#include "Camera.h"


std::vector<GameObject *> GameObject::registry;

GameObject::GameObject(
        std::string name,
        double x = 0.0,
        double y = 0.0,
        SDL_Texture *texture = nullptr,
        int x_origin = 0,
        int y_origin = 0,
        int totalFrames = 1,
        int numberOfAnimations = 1
) : name(std::move(name)),
    x_pos(x),
    y_pos(y),
    texture(texture),
    x_origin(x_origin),
    y_origin(y_origin),
    totalFrames(totalFrames),
    numberOfAnimations(numberOfAnimations),
    currentAnimation(0),
    currentFrame(0) {

    if (this->texture != nullptr) {
        SDL_QueryTexture(this->texture, nullptr, nullptr, &this->width, &this->height);
        this->frameWidth = this->width / this->totalFrames;
        this->frameHeight = this->height / this->numberOfAnimations;
    }

    registry.push_back(this);
}

void GameObject::setX(double xPos) {
    x_pos = xPos;
}

void GameObject::setY(double yPos) {
    y_pos = yPos;
}

GameObject::~GameObject() {
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

void GameObject::update(double deltaTime) {
    if (!is_active) { return; }

    deltaTime *= timeMultiplier;

    animationTimer += deltaTime;
    if (animationTimer >= 0.05) {
        currentFrame = (currentFrame + 1) % totalFrames;
        animationTimer = 0.0f;
    }
}

void GameObject::changeAnimation(int animationIndex) {
    if (animationIndex == currentAnimation) return;

    if (animationIndex < numberOfAnimations) {
        currentAnimation = animationIndex;
        currentFrame = 0;
    }
}

void GameObject::render() {
    if (!is_active) {
        return;
    }

    SDL_Rect srcRect = {
            currentFrame * frameWidth,
            currentAnimation * frameHeight,
            frameWidth,
            frameHeight
    };
    SDL_Rect destRect = {
            static_cast<int>(-Camera::x + x_pos) - x_origin + Game::getWidth() / 2,
            static_cast<int>(Camera::y - y_pos) - y_origin + Game::getHeight() / 2,
            static_cast<int>(frameWidth),
            static_cast<int>(frameHeight)
    };
    SDL_RenderCopyEx(Game::getRenderer(), texture, &srcRect, &destRect, 0, nullptr, flip ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
}

int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}

double GameObject::getY() {
    return this->y_pos;
}


