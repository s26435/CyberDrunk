#include <SDL_ttf.h>
#include "GUI.h"
#include "ResourceManager.h"
#include "Game.h"

void GUI::drawText(int x, int y, std::string text) {


    TTF_Font* font = ResourceManager::loadFont("font.ttf", 10);

    SDL_Color color = {255, 255, 255};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        printf("Nie udało się stworzyć powierzchni dla tekstu: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
    if (texture != nullptr)
    {
        SDL_Rect textRect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(Game::getRenderer(), texture, nullptr, &textRect);
        SDL_DestroyTexture(texture);
    }

    SDL_FreeSurface(surface);
}

void GUI::drawHealthBar(int hp){
    std::string text = " ";
    for(int i =0; i < hp; i++){
        text+="j";
    }
    TTF_Font* font = ResourceManager::loadFont("font2.ttf", 10);
    SDL_Color color = {255, 0, 0};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (surface == nullptr) {
        printf("Nie udało się stworzyć powierzchni dla tekstu: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::getRenderer(), surface);
    if (texture != nullptr)
    {
        SDL_Rect textRect = {400, 10, surface->w, surface->h};
        SDL_RenderCopy(Game::getRenderer(), texture, nullptr, &textRect);
        SDL_DestroyTexture(texture);
    }

    SDL_FreeSurface(surface);
}

