#include "BoxCollider.h"

CollisionResult BoxCollider::checkCollision(const BoxCollider& other) const {
    double dx = (x + width / 2) - (other.x + other.width / 2);
    double dy = (y + height / 2) - (other.y + other.height / 2);
    double overlapX = (width / 2 + other.width / 2) - std::abs(dx);
    double overlapY = (height / 2 + other.height / 2) - std::abs(dy);

    if (overlapX > 0 && overlapY > 0) {
        if (overlapX < overlapY) {
            return {true, dx < 0 ? -overlapX : overlapX, 0};
        } else {
            return {true, 0, dy < 0 ? -overlapY : overlapY};
        }
    }
    return {false, 0, 0};
}