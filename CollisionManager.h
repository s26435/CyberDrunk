//
// Created by Malak on 22.03.2024.
//

#ifndef CYBERDRUNK_COLLISIONMANAGER_H
#define CYBERDRUNK_COLLISIONMANAGER_H


#include "TestObject.h"
#include <SDL.h>
#include <vector>
#include "Item.h"
#include "Game.h"

class CollisionManager {
public:
    static void checkCollisions(double deltaTime) {

        for (auto& obj : TestObject::registry) {
            obj->test = false;
        }

        for (auto& obj1 : TestObject::registry) {
            if (!obj1->getCollider()) continue;

            for (auto& obj2 : TestObject::registry) {
                if (obj1 == obj2 || obj1->getName() == obj2->getName() || !obj2->getCollider()) continue;

                CollisionResult result = obj1->getCollider()->checkCollision(*obj2->getCollider());
                if (result.collided) {
                    obj1->test = true;
                    obj2->test = true;
                    double invMass1 = 10000.0;
                    double invMass2 = 10000.0;

                    if(result.collided){
                        if(obj1->getName() == "Player" && obj2->getName()=="spikes") Game::hitPlayer(1);
                        if(obj2->getName() == "Player" && obj1->getName()=="spikes") Game::hitPlayer(1);
                    }

                    if (result.overlapX != 0) {
                        obj1->velocityX += result.overlapX * invMass1 * deltaTime * 10.0;
                        obj2->velocityX -= result.overlapX * invMass2 * deltaTime* 10.0;
                    }
                    if (result.overlapY != 0) {
                        obj1->velocityY = 0;
                        obj2->velocityY = 0;
                        obj1->velocityY += result.overlapY * invMass1 * deltaTime * 10.0;
                        obj2->velocityY -= result.overlapY * invMass2 * deltaTime * 10.0;
                    }
                }
            }
        }
    }

};


#endif //CYBERDRUNK_COLLISIONMANAGER_H
