#ifndef UNTITLED_RESOURCEMANAGER_H
#define UNTITLED_RESOURCEMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <map>

class ResourceManager {
public:
    static bool initialize();
    static void shutdown();

    static SDL_Texture* loadTexture(const std::string& path);
    static TTF_Font* loadFont(const std::string& path, int fontSize);
    static Mix_Chunk* loadSound(const std::string& path);
    static Mix_Music* loadMusic(const std::string& path);

    static void freeTexture(const std::string& path);
    static void freeFont(const std::string& path);
    static void freeSound(const std::string& path);
    static void freeMusic(const std::string& path);

private:
    static std::map<std::string, SDL_Texture*> textures;
    static std::map<std::string, TTF_Font*> fonts;
    static std::map<std::string, Mix_Chunk*> sounds;
    static std::map<std::string, Mix_Music*> music;
};

#endif //UNTITLED_RESOURCEMANAGER_H
