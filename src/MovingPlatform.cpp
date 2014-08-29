#include "D2DResourceManager.hpp"
#include "MovingPlatform.hpp"

#include <cmath>
#include <iostream>

static int startx, starty;

static bool movingRight = true;

void MovingPlatform::init(float x, float y)
{
    m_x = x;
    m_y = y;

    m_image = D2DResourceManager::instance().getTexture("res/moving_platform.png").lock();

    startx = x;
    starty = y;
}

void MovingPlatform::update(float dt)
{
    static float x = 150.0f;
    if (movingRight){
        m_x += 150.0f * dt;

        if (m_x >= startx + 100.0f)
            movingRight = false;
    }

    else if (!movingRight){
        m_x -= 150.0f * dt;

        if (m_x <= startx - 100.0f)
            movingRight = true;
    }
}

void MovingPlatform::render(SDL_Renderer* renderer)
{
    m_image->render((int)m_x, (int)m_y, renderer);
}