/*
===============================================================================
* File: D2DAnimation.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Contains sequences of images to be displayed one after the other
===============================================================================
*/

#ifndef D2D_ANIMATION_HPP
#define D2D_ANIMATION_HPP

#include <fstream>
#include <memory>

#include <string>
#include <vector>

#include "json/json.h"

#include "D2DLogger.hpp"
#include "D2DSpritesheet.hpp"
#include "D2DTimer.hpp"

extern std::ofstream DEBUG_LOG;

class D2DAnimation {
  public:
    D2DAnimation();
    ~D2DAnimation();

    void loadFromFile(std::string path);
    void run();
    void render(int x, int y, SDL_Renderer* renderer);
    void reset();

    SDL_Rect* getCurrentFrame();

  private:
    // Some helper functions for loadFromFile()
    void getSpritesheet(Json::Value spritesheet);
    void loadFrames(Json::Value framesArray);

  private:
    std::shared_ptr<D2DSpritesheet> m_spritesheet;
    std::vector<SDL_Rect*> m_frames;

    D2DTimer m_timer;

    int m_currentFrame;

    // time is in milliseconds
    int m_updateTime;
    Uint32 m_timeSinceLast;

    D2DLogger logger;
};

#endif