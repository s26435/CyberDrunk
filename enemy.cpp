//
// Created by Mar on 16.05.2024.
//
#include "enemy.h"
#include "resourceManager.h"
#include <iostream>

Enemy::Enemy(
        const std::string& name,
        double x,
        double y,
        SDL_Texture* texture,
        int x_origin,
        int y_origin,
        int totalFrames,
        int numberOfAnimations
) : TestObject(name, x, y, texture, x_origin, y_origin, totalFrames, numberOfAnimations),
    texture(nullptr), spawnSound(nullptr) {
}

Enemy::~Enemy() {
    despawn();
}

void Enemy::spawn(double x, double y, const std::string& texturePath) {
    setActive(true);
    setPosition(x, y);
    std::cout << "Spawning at (" << x << ", " << y << ")" << std::endl; // Dodajemy komunikat debugowania
    texture = ResourceManager::loadTexture(texturePath);
    if (texture == nullptr) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    } else {
        setTexture(texture); // Użycie nowej metody setTexture
        std::cout << "Load successfuly: " << texturePath << std::endl;
    }

    spawnSound = ResourceManager::loadSound("haloHalo.wav");
    if (spawnSound != nullptr) {
        Mix_PlayChannel(-1, spawnSound, 0);
    }
}

void Enemy::despawn() {
    setActive(false);
        Mix_Chunk* deadSound = nullptr;
    deadSound = ResourceManager::loadSound("zgon21.wav");
    if (deadSound != nullptr) {
        Mix_PlayChannel(-1, deadSound, 0);
    }

    if (texture != nullptr) {
        ResourceManager::freeTexture("zombie.png");
        texture = nullptr;
    }

    if (spawnSound != nullptr) {
        Mix_HaltChannel(-1); // Zatrzymaj dźwięk odtwarzany na dowolnym kanale
        ResourceManager::freeSound("haloHalo.wav");
        spawnSound = nullptr;
    }
}