#ifndef CYBERDRUNK2137_PLATFORM_H
#define CYBERDRUNK2137_PLATFORM_H

#include <memory>
#include "GameObject.h"
#include "BoxCollider.h"
#include "TestObject.h"

class Platform:GameObject{
public:
    double getY();
    double getX();
    void setY(double y) override;
    void setX(double x) override;
    double getWidth();
    double getHeight();
    static std::vector<Platform *> registry;
    std::unique_ptr<BoxCollider> collider;
    explicit Platform(
            std::string name = "TestObject",
    double x = 0.0,
    double y = 0.0,
            SDL_Texture* texture = nullptr,
    int x_origin = 0,
    int y_origin = 0,
    int totalFrames = 1,
    int numberOfAnimations = 1,
    std::unique_ptr<BoxCollider> collider = nullptr
    ) : GameObject(std::move(name), x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations){
       this->collider = std::make_unique<BoxCollider>(x,y, this->width, this->height);
    }
    ~Platform() override;
    void render() override;
    void update(double deltaTime) override;
    [[nodiscard]] CollisionResult checkCollisionWith(const TestObject& other) const;
    std::unique_ptr<BoxCollider>& getCollider() {
        return collider;
    }
};

#endif //CYBERDRUNK2137_PLATFORM_H
