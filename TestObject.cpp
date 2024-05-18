#include "TestObject.h"
#include <cmath>
#include "BoxCollider.h"
#include "Game.h"
#include "Camera.h"

std::vector<TestObject *> TestObject::registry;


TestObject::~TestObject()
{
    auto it = std::find(registry.begin(), registry.end(), this);
    if (it != registry.end()) {
        registry.erase(it);
    }
}

CollisionResult TestObject::checkCollisionWith(const TestObject& other) const {
    return collider->checkCollision(*other.collider);
}

void TestObject::setTtl(double value) {
    this->ttl = value;
}

void TestObject::setVelocity(double x, double y) {
    setVelocityX(x);
    setVelocityY(y);
}

void TestObject::setVelocityX(double value) {
    this->velocityX = value;
}

void TestObject::setVelocityY(double value) {
    this->velocityY = value;
}

void TestObject::moveX(double x) {
    this->x_pos = x;
}

void TestObject::moveY(double y) {
    this->y_pos = y;
}

void TestObject::jump() {
    if (!isJumping) {
        setVelocityY(200 * 1.1);
        isJumping = true;
    }
}

void TestObject::update(double deltaTime) {
    GameObject::update(deltaTime);
    if (collider != nullptr)
    {
        collider->x = x_pos - x_origin;
        collider->y = y_pos;
        collider->width = width;
        collider->height = height;;
    }

    if(isLocked){
        this->x_pos = lockInPlaceX;
        this->y_pos = lockInPlaceY;
    }

    deltaTime *= timeMultiplier;

    if (ttl > 0) {
        life += deltaTime;
    }

    if (life > ttl) {
        this->~TestObject();
        return;
    }

    double previousY = y_pos;

    velocityX += -velocityX * 0.1 * deltaTime;
    velocityY += -velocityY * 0.1 * deltaTime;

   if (name == "Player")
  {
      velocityX += -velocityX * 15 * deltaTime;
  }

  velocityY += gravity * deltaTime;

  x_pos += velocityX * deltaTime;
  y_pos += velocityY * deltaTime;

  if (y_pos <= 0) {
      if (previousY != 0) {
          //on land do smth
      }
      y_pos = 0;
      velocityY = 0.0;
      isJumping = false;
  }
}

void TestObject::render() {
  GameObject::render();

  if(this->collider != nullptr)
  {
      if (test)
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

  if (name == "Player")
  {
      //SDL_SetRenderDrawColor(Game::getRenderer(), 255, 255, 255, SDL_ALPHA_OPAQUE);
      //SDL_RenderDrawLine(Game::getRenderer(), Mouse::gameToScreen(x_pos, y_pos).first, Mouse::gameToScreen(x_pos, y_pos).second - 12, Mouse::getScreenX(),  Mouse::getScreenY());
  }
}