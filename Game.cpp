#include "Game.h"
#include "Window.h"
#include <iostream>
#include <random>
#include "ResourceManager.h"
#include "GameObject.h"
#include "Environment.h"
#include "MobObject.h"
#include "GUI.h"
#include "Mouse.h"
#include "CollisionManager.h"
#include "Inventory.h"
#include "PauseMenu.h"
#include "Platform.h"
#include "enemy.h"
#include <memory>


SDL_Renderer *Game::renderer = nullptr;
MobObject* Game::player = nullptr;
int Game::width = 500;
int Game::height = 300;
double Game::time = 0;
unsigned int Game::fps = 0;
double Game::worldTimeMultiplier = 1.0f;
double Game::playerTimeMultiplier = 1.0f;
Inventory* Game::inv= nullptr;
PauseMenu* Game::pause= nullptr;
Button* Game::resume= nullptr;
Button* Game::exit = nullptr;

bool isPaused = false;
bool running = true;
bool dead = false;

Mix_Chunk* stepSound = nullptr;
int stepChannel = -1;
Mix_Music* Game::backgroundMusic = nullptr;

std::unique_ptr<Enemy> enemy;
std::unique_ptr<Enemy> Game::enemy = nullptr;

bool Game::initialize() {
    renderer = SDL_CreateRenderer(Window::getWindow(), -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }
    inv = new Inventory();
    double ar = (double) Window::width / (double) Window::height;
    width = (int) (height * ar);
    SDL_RenderSetLogicalSize(renderer, width, height);
    if (!ResourceManager::initialize()) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "ResourceManager initialization failed!");
        return false;
    }
    isPaused = false;

    auto spikes = new TestObject("spikes",300, 0, ResourceManager::loadTexture("spikes.png"),100, 29);
    spikes->lockInPlace(300, 0);
    new TestObject("dupa" , -200, 200, ResourceManager::loadTexture("imperator.png"),29,29+40);
    player = new MobObject("Player", -100, 200, ResourceManager::loadTexture("anim.png"), 8, 29, 12, 3);
    Environment::init();
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        std::cerr << "SDL_mixer could not initialize!" << Mix_GetError() << std::endl;
    }
    stepSound = ResourceManager::loadSound("step.wav");
    if (!stepSound){
        std::cerr << "Failed to load step sound" << Mix_GetError() << std::endl;
        return false;
    }
    backgroundMusic = ResourceManager::loadMusic("music.mp3");
    if (!backgroundMusic) {
        std::cerr << "Failed to load background music: " << Mix_GetError() << std::endl;
        return false;
    }
    if (backgroundMusic) {
        Mix_PlayMusic(backgroundMusic, -1);  // Odtwarzaj muzykę w pętli
    }
    return true;
}

float generateRandom(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

void Game::update(double deltaTime, bool pause1) {
    Mouse::update();
    bool isMoving = false;
    const Uint8 *keystates = SDL_GetKeyboardState(nullptr);
    if (!pause1) {
        CollisionManager::checkCollisions(deltaTime);
        Environment::update(deltaTime);
        if (keystates[SDL_SCANCODE_W]) {
            player->jump();
        }
        if (keystates[SDL_SCANCODE_ESCAPE]) {
            isPaused = true;
        }
        if (keystates[SDL_SCANCODE_S]) {
            //implementacja szybowania
            //player->velocityY = -30.0f;
        }

        if (keystates[SDL_SCANCODE_A]) {
            player->moveLeft();
            isMoving = true;
        }

        if (keystates[SDL_SCANCODE_D]) {
            player->moveRight();
            isMoving = true;
        }

        if (keystates[SDL_SCANCODE_SPACE] && !player->isJumping) {
            player->attack();
            short facing;
            if (player->velocityX < 0) facing = -1;
            else facing = 1;
            auto *szczau = new TestObject("szczau", player->getX() + (8 * facing), player->getY() + 16,
                    ResourceManager::loadTexture("star.png"), 0, 0);
            szczau->setVelocity(200 * facing, 0);
            szczau->setTtl(2);
            szczau->setTimeMultiplier(worldTimeMultiplier);
            szczau->gravity = 0;
        }
        if (keystates[SDL_SCANCODE_Q]) {
            updateTimeDilation(playerTimeMultiplier, worldTimeMultiplier * 0.99);
        }
        if (keystates[SDL_SCANCODE_E]) {
            updateTimeDilation(playerTimeMultiplier, worldTimeMultiplier * 1.01);
        }
        if (keystates[SDL_SCANCODE_Z]) {
            updateTimeDilation(playerTimeMultiplier * 0.99, worldTimeMultiplier);
        }
        if (keystates[SDL_SCANCODE_C]) {
            updateTimeDilation(playerTimeMultiplier * 1.01, worldTimeMultiplier);
        }
        for (auto obj: GameObject::registry) {
            obj->update(deltaTime);
        }

        if (keystates[SDL_SCANCODE_F]){
            player->attackMelee();
        }

        if (keystates[SDL_SCANCODE_G]){
            player->granade();
            player->getDamage(5);
        }

        if (keystates[SDL_SCANCODE_H]){
            if (!enemy) {
                int x = rand() % 300;
                enemy = std::make_unique<Enemy>("enemy", 0, 0, ResourceManager::loadTexture("zombie.png"), 20, 20, 1, 1);
                enemy->spawn(x, 20, "zombie.png");
            }
        }
        if(isMoving&&!player->isJumping){
            if (stepChannel == -1){
                stepChannel = Mix_PlayChannel(-1, stepSound, -1);
            }
        } else {
            if (stepChannel != -1){
                Mix_HaltChannel(stepChannel);
                stepChannel = -1;
            }
        }
        Camera::follow(player->getX(), player->getY(), deltaTime);
    } else {
        if (keystates[SDL_SCANCODE_ESCAPE]) {
            isPaused = false;
        }
    }
    if(player->life <= 0) {
        isPaused = true;
        dead = true;
    }
}

void Game::hitPlayer(int damage){
    player->getDamage(damage);
    player->canGetDamage = false;
}

void Game::render() {
    using namespace std;
    SDL_SetRenderDrawColor(renderer, 0x3a, 0xa5, 0xdc, 0xFF);
    SDL_RenderClear(renderer);
    Environment::render(time);
    for (auto obj: GameObject::registry) {
        obj->render();
    }
    if(isPaused&&!dead){
        if(pause == nullptr){
            pause = new PauseMenu("Pause Menu");
            resume = new Button("resumeButton",0, 0, ResourceManager::loadTexture("resume.png"));
            exit = new Button("exitButton", 0,0, ResourceManager::loadTexture("exit.png"));
        }
        pause->setPosition(Camera::x-100, Camera::y+60);
        pause->render();
        resume->setPosition(Camera::x-10, Camera::y+10);
        resume->render();
        exit->setPosition(Camera::x-10, Camera::y-10);
        exit->render();
    }else if(!isPaused){
        if(pause != nullptr){
            pause->~PauseMenu();
            resume->~Button();
            exit->~Button();
            pause = nullptr, resume = nullptr, exit = nullptr;
        }
    }

    if(dead){
        if(exit== nullptr) {
            exit = new Button("exitButton", 0, 0, ResourceManager::loadTexture("exit.png"));
            pause = new PauseMenu("exit menu", 0, 0, ResourceManager::loadTexture("endGame.png"));
        }
        pause->setPosition(Camera::x-100, Camera::y+60);
        pause->render();
        exit->setPosition(Camera::x-20, Camera::y+10);
        exit->render();
    }

    int mouseX, mouseY;
    Uint32 mouseState = SDL_GetMouseState(&mouseX, &mouseY);
    int w;
    int h;
    SDL_RenderGetLogicalSize(renderer, &w, &h);
    if ((mouseState & SDL_BUTTON_LMASK) != 0) {
        if(isPaused){
            if(resume!= nullptr){
                double rx =  resume->getX();
                double ry = resume->getY();
                double ex =  exit->getX();
                double ey = exit->getY();
                auto mx = Mouse::getGameX();
                auto my = Mouse::getGameY();
                if( (mx >= rx)  && (my <= ry) && (mx <= rx + resume->getWidth()) && (my >= ry - resume->getHeight())){
                    isPaused = !resume->onClick();
                }
                if( (mx >= ex)  && (my <= ey) && (mx <= ex + exit->getWidth()) && (my >= ey - exit->getHeight())){
                    running = exit->onClick();
                }
            }
            if(dead){
                double ex =  exit->getX();
                double ey = exit->getY();
                auto mx = Mouse::getGameX();
                auto my = Mouse::getGameY();
                if( (mx >= ex)  && (my <= ey) && (mx <= ex + exit->getWidth()) && (my >= ey - exit->getHeight())){
                    running = exit->onClick();
                }
            }
        }
    }
    GUI::drawHealthBar(player->life);
    std::string currentPositionText = std::to_string(player->getY()) + ", " + std::to_string(Camera::y);
    //GUI::drawText(0, 0, currentPositionText);
    std::string currentPositionText2 = "Cam: " + std::to_string(Camera::x) + ", " + std::to_string(Camera::y);
    //GUI::drawText(0, 80, currentPositionText2);
    std::string currentPositionText55 = "Mouse2: " + std::to_string(TestObject::registry.size()) + ", " + std::to_string(Mouse::getScreenY());
    //GUI::drawText(0, 40, currentPositionText55);
    std::string currentPositionText4 = "FPS: " + std::to_string(fps);
    //GUI::drawText(0,40, "dead: " + std::to_string(dead));
    GUI::drawText(0, 0, currentPositionText4);
    GUI::drawText(450, 30, "Imperator: " + std::to_string(inv->getImperatorAmount()));
    GUI::drawText(450, 50, "Special: " + std::to_string(inv->getSpecialAmount()));
    GUI::drawText(450, 70, "Romper: " + std::to_string(inv->getRomperAmount()));
    //GUI::drawText(450, 80, "isPaused: " + std::to_string(isPaused));
    SDL_RenderPresent(renderer);
}

void Game::loop() {
    SDL_Event event;

    unsigned int frameStart;
    unsigned int frameTime = 0;

    unsigned int frameCount = 0;
    unsigned int lastFpsUpdate = 0;

    while (running) {
        frameStart = SDL_GetTicks();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Rain();
        double deltaTime = (double) frameTime / 1000.0;
        time += deltaTime;
        update(deltaTime, isPaused);
        render();
        frameTime = SDL_GetTicks() - frameStart;
        frameCount++;
        if (frameStart - lastFpsUpdate >= 1000.0) {
            fps = frameCount / ((frameStart - lastFpsUpdate) / 1000.0);
            frameCount = 0;
            lastFpsUpdate = frameStart;
        }
    }
}

void Game::cleanUp() {
    ResourceManager::shutdown();
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (stepSound){
        Mix_FreeChunk(stepSound);
        stepSound = nullptr;
    }
    if (backgroundMusic) {
        Mix_HaltMusic();
        Mix_FreeMusic(backgroundMusic);
        backgroundMusic = nullptr;
    }
    Mix_CloseAudio();
    Window::cleanUp();
}

SDL_Renderer *Game::getRenderer() {
    return renderer;
}

void Game::Rain(bool isRaining) {
        if(isRaining){
            for (int i = 0; i < 10; i++) {
                TestObject *a = new TestObject("Rain", generateRandom(-1.1, 1.1) * Game::width + player->getX(), 300,
                                               ResourceManager::loadTexture("sand.png"), 0, 0, 1, 1);
                a->setTtl(3);
                a->setTimeMultiplier(worldTimeMultiplier);
            }
        }
}
