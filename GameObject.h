#ifndef UNTITLED_GAME_OBJECT_H
#define UNTITLED_GAME_OBJECT_H

#include <SDL.h>
#include <utility>
#include <vector>
#include "string"

class GameObject {
protected:
    unsigned int object_id=NAN;

    bool is_active = true;

    std::string name;
public:
    double getY();

protected:

    double x_pos;
    double y_pos;

    int x_origin;
    int y_origin;


    int width;
    int height;
public:
    int getWidth() const;

    int getHeight() const;

protected:
    int frameWidth;
    int frameHeight;

    int currentAnimation;
    int currentFrame;

    int totalFrames = 1;
    int numberOfAnimations = 1;

    double animationTimer = 0.0;

    double timeMultiplier = 1.0f;

    bool flip = false;

    SDL_Texture* texture;

public:
    static std::vector<GameObject*> registry;

    GameObject(std::string name, double x, double y, SDL_Texture* texture, int x_origin, int y_origin, int totalFrames, int numberOfAnimations);
    virtual ~GameObject();

    virtual void update(double deltaTime);
    virtual void render();

    void changeAnimation(int animationIndex);

    [[nodiscard]] unsigned int getId() const{
        return this->object_id;
    }
    [[nodiscard]] double getY() const{
        return this->y_pos;
    }
    [[nodiscard]] double getX() const{
        return this->x_pos;
    }

    [[nodiscard]]auto  getName() const -> std::string {
        return this->name;
    }
    void setID(int id){
        this->object_id = id;
    }

    void setActive(bool value){
        this->is_active = value;
    }

    void setTimeMultiplier(double multiplier) {
        timeMultiplier = multiplier;
    }

    float getTimeMultiplier() const {
        return timeMultiplier;
    }

    virtual void setX(double xPos);

    virtual void setY(double yPos);


};

#endif //UNTITLED_GAME_OBJECT_H
