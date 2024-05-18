#ifndef CYBERDRUNK_ITEM_H
#define CYBERDRUNK_ITEM_H

#include <string>
#include <optional>
#include <random>
#include <iostream>
#include "SDL_mixer.h"
#include "ResourceManager.h"

class Item {
private:
    unsigned int id;
    std::string name;
    float dropChance;
    std::vector<Mix_Chunk*> sound = std::vector<Mix_Chunk*>(3);

public:
    Item(unsigned int id, std::string name, float dropChance, const std::vector<std::string>& soundPaths)
            : id(id), name(std::move(name)), dropChance(dropChance) {
        for(int i =0; i < soundPaths.size(); i++){
            sound[i] = ResourceManager::loadSound(soundPaths[i]);
            std::cout << "Loaded: " << soundPaths[i] << std::endl;
            if (!sound[i]) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Nie udało się załadować dźwięku: %s", Mix_GetError());
        }
    }
    void use(){
        std::cout << sound.size();
        if (!sound.empty()) {
            std::cout << "Dupa" << std::endl;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(0,  (int)sound.size()- 1);
            Mix_PlayChannel(-1, sound[dis(gen)], 0);
        }
    }
};

#endif //CYBERDRUNK_ITEM_H
