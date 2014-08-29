/*
===============================================================================
* File: MovingPlatform.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Platform that moves on the x axis
===============================================================================
*/

#ifndef MOVING_PLATFORM_HPP
#define MOVING_PLATFORM_HPP

#include <memory>

#include "D2DTexture.hpp"

class MovingPlatform {
  public:
    void init(float x, float y);
    void update(float dt);
    void render(SDL_Renderer* renderer);

  private:
    float m_x;
    float m_y;

    std::shared_ptr<D2DTexture> m_image;
};

#endif