#ifndef CYBERDRUNK_TESTOBJECT_H
#define CYBERDRUNK_TESTOBJECT_H

#include "GameObject.h"
#include "BoxCollider.h"
#include <string>
#include <SDL.h>
#include <memory>
#include <utility>

class TestObject : public GameObject {

public:
    static std::vector<TestObject*> registry;

    double velocityX, velocityY;
    double gravity;
    double ttl;
    double life;
    bool isJumping;
    bool isLocked = false;
    double lockInPlaceX = NAN;
    double lockInPlaceY = NAN;
    bool test;

    TestObject(
            std::string name = "TestObject",
            double x = 0.0,
            double y = 0.0,
            SDL_Texture* texture = nullptr,
            int x_origin = 0,
            int y_origin = 0,
            int totalFrames = 1,
            int numberOfAnimations = 1
    ) : GameObject(std::move(name), x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations),
    velocityX(0.0),
    velocityY(0.0),
    gravity(-200),
    ttl(0),
    life(0),
    isJumping(false),
    test(true) {
            this->collider = std::make_unique<BoxCollider>(x, y, width, height);
            registry.push_back(this);
    }

    ~TestObject() override;

    void lockInPlace(double x, double y){
        lockInPlaceX = x;
        lockInPlaceY = y;
        isLocked = true;
    }

    void unlock(){
        isLocked = false;
    }

    std::unique_ptr<BoxCollider>& getCollider() {
        return collider;
    }

    [[nodiscard]] CollisionResult checkCollisionWith(const TestObject& other) const;

    void setTtl(double ttl);
    void setVelocity(double x, double y);
    void setVelocityX(double value);
    void setVelocityY(double value);

    TestObject& operator=(TestObject&& other) noexcept {
        if (this != &other) {
            GameObject::operator=(std::move(other));
            collider = std::move(other.collider);
        }
        return *this;
    }

    void moveX(double x);
    void moveY(double y);
    void jump();
    void update(double deltaTime) override;
    void render() override;

    std::unique_ptr<BoxCollider> collider;
};
#endif //CYBERDRUNK_TESTOBJECT_H
