/*
===============================================================================
* File: main.cpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Entry point for sdl tutorial program
===============================================================================
*/

#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>

#include "json/json.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "D2DAnimation.hpp"
#include "D2DMusic.hpp"
#include "D2DResourceManager.hpp"
//#include "D2DSoundEffect.hpp"
#include "D2DSpritesheet.hpp"
#include "D2DTexture.hpp"
#include "TileMap.hpp"
#include "D2DTimer.hpp"

#include "Mario.hpp"
#include "MovingPlatform.hpp"

const int WIDTH = 640;
const int HEIGHT = 480;

bool quit = false;

SDL_Window* window = nullptr;

SDL_Renderer* renderer = nullptr;

D2DTexture background;

std::shared_ptr<D2DMusic> marioMusic;

// I REALLY NEED TO ADD AN ENTITY MANAGER
Mario marioPlayer;

MovingPlatform movingPlatform;

TileMap map;

SDL_Event e;

bool init(){
    bool success = true;

    // Initialize SDL
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());

        success = false;
    }

    else {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT,
                                  SDL_WINDOW_SHOWN);

        if (window == nullptr){
            printf("Window could not be created! SDL error: %s\n",
                   SDL_GetError());

            success = false;
        }

        else {
            renderer = SDL_CreateRenderer(window, -1,
                                          SDL_RENDERER_ACCELERATED);

            if (renderer == nullptr){
                printf("Renderer could not be created! SDL error: %s\n",
                       SDL_GetError());

                success = false;
            }

            else {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags)){
                    printf("SDL_image could not initialize! SDL_image error: %s\n",
                           IMG_GetError());

                    success = false;
                }

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                    printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());

                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
    bool success = true;

    background.loadFromFile("res/background.png", renderer);

    D2DResourceManager::instance().loadResources("res/resourcesjson.res",
                                                 renderer);

    std::weak_ptr<D2DMusic> tempMusic(D2DResourceManager::instance().getMusic("res/mario_1-1.wav"));

    marioMusic = tempMusic.lock();

    /*if (!map.loadFromFile("map")){
        printf("Failed to load TileMap map");

        success = false;
    }*/

    map.loadFromFile("res/map");

    return success;
}

void close(){
    //background.free();

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    window = nullptr;
    renderer = nullptr;

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    D2DTimer updateTimer;

    if (!init()){
        printf("Failed to initialize!\n");
    }

    else {
        if (!loadMedia()){
            printf("Failed to load media!\n");
        }

        else {
            float x = 100.f;
            float y = 300.f;

            marioPlayer.init();
            movingPlatform.init(250, 250);
            
            marioMusic->play();
            Mix_VolumeMusic(MIX_MAX_VOLUME / 2);

            updateTimer.start();
            while (!quit){
                while (SDL_PollEvent(&e) != 0){
                    if (e.type == SDL_QUIT)
                        quit = true;
                }

                // handle input
                marioPlayer.handleInput(e);

                // update player, entities, etc. this should go in an update
                // function
                float delta = updateTimer.getTicks() / 1000.0f;
                marioPlayer.update(delta, map);
                movingPlatform.update(delta);

                updateTimer.start();

                // render player, entities, etc. this should go in a render
                // function
                SDL_RenderClear(renderer);

                background.render(0, 0, renderer);
                map.render(renderer);

                movingPlatform.render(renderer);
                marioPlayer.render(renderer);

                SDL_RenderPresent(renderer);
            }
        }
    }

    marioMusic->stop();

    close();

    return 0;
}