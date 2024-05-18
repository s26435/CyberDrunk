//
// Created by Malak on 19.03.2024.
//

#ifndef CYBERDRUNK_ENVIRONMENT_H
#define CYBERDRUNK_ENVIRONMENT_H

#include <vector>
#include "SDL.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "Game.h"

// Struktura reprezentująca pojedynczą warstwę tła
struct BackgroundLayer {
    SDL_Texture* texture;


    double xPosition;
    double yPosition;

    int yOffset;

    double speedX;
    double speedY;

    double animX;
};

class Environment {

public:
    static std::vector<BackgroundLayer> layers;
    static void init() {
        layers = {
                {ResourceManager::loadTexture("layer2.png"), 0, 0,(Game::getHeight() / 2) - 100, 0.15f, 0.5f, 10}, // Dalsza warstwa, porusza się wolniej
                {ResourceManager::loadTexture("layer1.png"), 0, 0,(Game::getHeight() / 2 ) - 100, 0.2f, 0.7f, 0},
                {ResourceManager::loadTexture("layer0.png"), 0, 0,(Game::getHeight() / 2 ) - 138, 0.45f, 1, 0},
                {ResourceManager::loadTexture("layerBase.png"), 0, 0,(Game::getHeight() / 2) - 20, 1.0f, 1, 0},
        };
    }


    static void update(double deltaTime) {
        for (auto &layer: layers) {
            layer.yPosition = Camera::y * layer.speedY;
            layer.xPosition = -Camera::x * layer.speedX ;
        }
    }

    static void render(float time)
    {
        for (const auto &layer : layers) {
            for (int i = -4; i <= 4; ++i) {
                SDL_Rect destRect = {i * 256 + (static_cast<int>(layer.xPosition + layer.animX * time)) % 256,
                                     layer.yOffset + static_cast<int>(layer.yPosition), 256, 128};
                SDL_RenderCopy(Game::getRenderer(), layer.texture, nullptr, &destRect);
            }
        }
    };
};


#endif //CYBERDRUNK_ENVIRONMENT_H