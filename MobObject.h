#ifndef CYBERDRUNK_MOBOBJECT_H
#define CYBERDRUNK_MOBOBJECT_H


#include "TestObject.h"
#include "Item.h"
#include <string>
#include <SDL.h>
#include <memory>
#include "enemy.h"
class MobObject : public TestObject {
public:
    static std::vector<MobObject*> registry;

    int life = 10;

    bool canGetDamage = true;
    bool isJumping = false;
    bool isAttacking = false;
    bool isRunning = false;
    bool isSprinting = false;

    int currentFrame = 0;

    Item* currentWeapon = nullptr;
    double attackSpeed = 0.0;
    double shotTime = 0.0;
    double attackTime = 0.0;
    double invisibilityTime = 0.0;

    MobObject(
    std::string name = "TestObject",
    double x = 0.0,
    double y = 0.0,
    SDL_Texture* texture = nullptr,
    int x_origin = 0,
    int y_origin = 0,
    int totalFrames = 1,
    int numberOfAnimations = 1
    );

    void onCollide();

    ~MobObject() override;

    MobObject& operator=(MobObject&& other) noexcept {
        if (this != &other) {
            GameObject::operator=(std::move(other));
            collider = std::move(other.collider);
        }
        return *this;
    }

    void getDamage(int damage);
    void moveLeft();
    void moveRight();
    void jump();
    void attack();
    void update(double deltaTime) override;
    void render() override;
    void attackMelee();
    void granade();

};

#endif //CYBERDRUNK_MOBOBJECT_H
