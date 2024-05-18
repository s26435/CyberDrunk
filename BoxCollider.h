#ifndef CYBERDRUNK_BOXCOLLIDER_H
#define CYBERDRUNK_BOXCOLLIDER_H

#include "GameObject.h"

struct CollisionResult {
    bool collided;
    double overlapX, overlapY;
};

class BoxCollider {
public:
    double x, y;
    double width, height;

    BoxCollider(double x, double y, double width, double height)
            : x(x), y(y), width(width), height(height) {}

    CollisionResult checkCollision(const BoxCollider& other) const;
};


#endif //CYBERDRUNK_BOXCOLLIDER_H
