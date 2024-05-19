//
// Created by Mar on 16.05.2024.
//

#ifndef CYBERDRUNK_ENEMY_H
#define CYBERDRUNK_ENEMY_H


#include "TestObject.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
class Enemy : public TestObject {
public:
    Enemy(
            const std::string& name = "Enemy",
            double x = 0.0,
            double y = 0.0,
            SDL_Texture* texture = nullptr,
            int x_origin = 10,
            int y_origin = 10,
            int totalFrames = 1,
            int numberOfAnimations = 1
    );

    ~Enemy() override;

    void spawn(double x, double y, const std::string& texturePath);
    void despawn();

private:
    SDL_Texture* texture;
    Mix_Chunk* spawnSound;
};
//class Enemy : public TestObject {
//public:
//    Enemy(double x = 0.0, double y = 0.0, int x_origin = 0, int y_origin = 0, int totalFrames = 1, int numberOfAnimations = 1);
//
//    void spawn(double x, double y, const std::string& texturePath ); // Funkcja do przyzwania przeciwnika na planszę
//    void die(); // Funkcja do znikania przeciwnika z planszy
//};


#endif //CYBERDRUNK_ENEMY_H
