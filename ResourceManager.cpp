#include <iostream>
#include "ResourceManager.h"
#include "Game.h"

std::map<std::string, SDL_Texture*> ResourceManager::textures;
std::map<std::string, TTF_Font*> ResourceManager::fonts;
std::map<std::string, Mix_Chunk*> ResourceManager::sounds;
std::map<std::string, Mix_Music*> ResourceManager::music;

bool ResourceManager::initialize() {
    //IMG
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL_image: %s", IMG_GetError());
        return false;
    }

    //AUDIO
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_mixer could not initialize! SDL_mixer Error: %s", Mix_GetError());
        return false;
    }

    //FONT
    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", TTF_GetError());
        return false;
    }


    return true;
}

void ResourceManager::shutdown() {
    for (auto& texture : textures) {
        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto& font : fonts) {
        TTF_CloseFont(font.second);
    }
    fonts.clear();

    for (auto& sound : sounds) {
        Mix_FreeChunk(sound.second);
    }
    sounds.clear();

    for (auto& m : music) {
        Mix_FreeMusic(m.second);
    }
    music.clear();

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
}

SDL_Texture* ResourceManager::loadTexture(const std::string& path) {
    if (textures.find(path) == textures.end()) {
        SDL_Texture* newTexture = IMG_LoadTexture(Game::getRenderer(), path.c_str());
        if (newTexture == nullptr) {
            std::cerr << "Unable to load texture " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
            return nullptr;
        }
        textures[path] = newTexture;
    }
    return textures[path];
}

TTF_Font* ResourceManager::loadFont(const std::string& path, int fontSize) {
    std::string key = path + std::to_string(fontSize);
    if (fonts.find(key) == fonts.end()) {
        TTF_Font* newFont = TTF_OpenFont(path.c_str(), fontSize);
        if (newFont == nullptr) {
            //std::cerr << "Unable to load font " << path << "! SDL_ttf Error: " << TTF_GetError() << std::endl;
            return nullptr;
        }
        fonts[key] = newFont;
    }
    return fonts[key];
}

Mix_Chunk* ResourceManager::loadSound(const std::string& path) {
    if (sounds.find(path) == sounds.end()) {
        Mix_Chunk* newSound = Mix_LoadWAV(path.c_str());
        if (newSound == nullptr) {
            //std::cerr << "Unable to load sound " << path << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return nullptr;
        }
        sounds[path] = newSound;
    }
    return sounds[path];
}

Mix_Music* ResourceManager::loadMusic(const std::string& path) {
    if (music.find(path) == music.end()) {
        Mix_Music* newMusic = Mix_LoadMUS(path.c_str());
        if (newMusic == nullptr) {
            //::cerr << "Unable to load music " << path << "! SDL_mixer Error: " << Mix_GetError() << std::endl;
            return nullptr;
        }
        music[path] = newMusic;
    }
    return music[path];
}

void ResourceManager::freeTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it != textures.end()) {
        SDL_DestroyTexture(it->second);
        textures.erase(it);
    }
}

void ResourceManager::freeFont(const std::string& path) {
    auto it = fonts.find(path);
    if (it != fonts.end()) {
        TTF_CloseFont(it->second);
        fonts.erase(it);
    }
}

void ResourceManager::freeSound(const std::string& path) {
    auto it = sounds.find(path);
    if (it != sounds.end()) {
        Mix_FreeChunk(it->second);
        sounds.erase(it);
    }
}

void ResourceManager::freeMusic(const std::string& path) {
    auto it = music.find(path);
    if (it != music.end()) {
        Mix_FreeMusic(it->second);
        music.erase(it);
    }
}