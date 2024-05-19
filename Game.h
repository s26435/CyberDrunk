#ifndef UNTITLED_GAME_H
#define UNTITLED_GAME_H


#include <SDL.h>
#include "MobObject.h"
#include "Inventory.h"
#include "PauseMenu.h"
#include <SDL_mixer.h>
#include "enemy.h"

extern Mix_Chunk* stepSound;
extern int stepChannel;

class Game {
public:
    static MobObject* player;
    static std::unique_ptr<Enemy> enemy;
    static unsigned int fps;
    static void hitPlayer(int damage =1);
    static bool initialize();

    static void update(double deltaTime, bool pause1 = false);
    static void render();

    static void loop();

    static void cleanUp();
    static SDL_Renderer* getRenderer();

    static int getWidth() {
        return width;
    }

    static int getHeight() {
        return height;
    }

    static void Rain(bool isRaining=false);

    static void updateTimeDilation(double playerMultiplier, double worldMultiplier) {

        if (playerMultiplier <= 0)
        {
            playerMultiplier = 0;
        }

        if (playerMultiplier > 1)
        {
            playerMultiplier = 1;
        }

        if (worldMultiplier <= 0)
        {
            worldMultiplier = 0;
        }

        if (worldMultiplier > 1)
        {
            worldMultiplier = 1;
        }

        playerTimeMultiplier = playerMultiplier;
        worldTimeMultiplier = worldMultiplier;

        player->setTimeMultiplier(playerTimeMultiplier);

        for (auto& obj : GameObject::registry) {
            if (obj != player) {
                obj->setTimeMultiplier(worldTimeMultiplier);
            }
        }
    }

    static double playerTimeMultiplier;
    static double worldTimeMultiplier;
    static Mix_Music* backgroundMusic;
private:
    static SDL_Renderer* renderer;

    static int width, height;
    static double time;
    static Inventory* inv;
    static PauseMenu* pause;
    static Button* resume;
    static Button* exit;

};

#endif //UNTITLED_GAME_H
