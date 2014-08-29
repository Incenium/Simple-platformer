/*
===============================================================================
* File: Mario.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Main character, the player, Mario
===============================================================================
*/

#ifndef MARIO_HPP
#define MARIO_HPP

#include <fstream>
#include <memory>

#include "SDL2/SDL.h"

#include "D2DAnimation.hpp"
#include "D2DLogger.hpp"

extern std::ofstream DEBUG_LOG;

class TileMap;

class Mario {
  public:
    Mario();
    ~Mario();

    bool init();

    void handleInput(SDL_Event e);
    void update(float delta, TileMap& level);
    void render(SDL_Renderer* renderer);

  private:
    float m_x, m_y;
    float m_xvel;
    float m_yvel;

    enum Animations {
        MARIO_RUNNING_RIGHT,
        MARIO_RUNNING_LEFT,
        //MARIO_JUMPING_RIGHT,
        //MARIO_JUMPING_LEFT
    };

    int m_currentAnimation;

    std::shared_ptr<D2DAnimation> m_animations[2];

    SDL_Rect m_collBox;
};

#endif