#include "D2DResourceManager.hpp"
#include "Mario.hpp"
#include "TileMap.hpp"
#include <iostream>
#include <cmath>

static bool isJumping = false;

Mario::Mario()
{
    m_x = 200.0f;
    m_y = 200.0f;

    m_xvel = 0.0f;
    m_yvel = 0.0f;

    m_currentAnimation = 0;

    for (int i = 0; i < 2; i++)
        m_animations[i] = nullptr;

    m_collBox = {(int)m_x, (int)m_y, 0, 0};
}

Mario::~Mario()
{
    for (int i = 0; i < 2; i++)
        m_animations[i] = nullptr;
}

bool Mario::init()
{
    bool success = true;

    m_x = 200.0f;
    m_y = 200.0f;

    m_xvel = 0.0f;
    m_yvel = 0.0f;

    m_currentAnimation = 0;

    D2DResourceManager& resManager = D2DResourceManager::instance();

    m_animations[MARIO_RUNNING_RIGHT] = resManager.getAnimation("res/mario_running_right.animation").lock();

    if (m_animations[MARIO_RUNNING_RIGHT] == nullptr){
        //DEBUG_LOG << "Unable to load mario running right animation" << std::endl << std::endl;

        success = false;
    }

    m_animations[MARIO_RUNNING_LEFT] = resManager.getAnimation("res/mario_running_left.animation").lock();

    if (m_animations[MARIO_RUNNING_LEFT] == nullptr){
        //DEBUG_LOG << "Unable to load mario running left animation" << std::endl << std::endl;

        success = false;
    }

    return success;
}

void Mario::handleInput(SDL_Event e)
{
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_RIGHT]){
        if (m_currentAnimation != MARIO_RUNNING_RIGHT)
            m_currentAnimation = MARIO_RUNNING_RIGHT;

        m_animations[m_currentAnimation]->run();
        m_xvel = 200.0f;
    }

    else if (keystates[SDL_SCANCODE_LEFT]){
        if (m_currentAnimation != MARIO_RUNNING_LEFT)
            m_currentAnimation = MARIO_RUNNING_LEFT;

        m_animations[m_currentAnimation]->run();
        m_xvel = -200.0f;
    }

    else {
        m_animations[m_currentAnimation]->reset();
        m_xvel = 0.0f;
    }

    if (keystates[SDL_SCANCODE_UP]){
        if (!isJumping){
            isJumping = true;

            m_yvel = -420.0f;
        }
    }
}

void Mario::update(float delta, TileMap& level)
{
    std::vector<SDL_Rect> tileRects = level.getCollidableTileRects();

    float gravity = 0.095f;
    m_yvel += gravity;
    if (m_yvel >= 550.0f)
        m_yvel = 550.0f;

    m_collBox.w = 18;
    m_collBox.h = 28;

    m_x += m_xvel * delta;
    m_collBox.x = (int)m_x;
    for (int i = 0; i < tileRects.size(); i++){
        SDL_Rect intersect;
        SDL_Rect tileRect = {tileRects[i].x, tileRects[i].y,
                             tileRects[i].w, tileRects[i].h};

        if (SDL_IntersectRect(&m_collBox, &tileRect, &intersect) == SDL_TRUE){
            if (m_xvel > 0.0f){
                m_x = m_x - intersect.w;
                m_collBox.x = (int)m_x;
            }

            else if (m_xvel < 0.0f){
                m_x = m_x + intersect.w;
                m_collBox.x = (int)m_x;
            }
        }
    }

    m_y += m_yvel * delta;
    m_collBox.y = (int)m_y;
    for (int i = 0; i < tileRects.size(); i++){
        SDL_Rect intersect;
        SDL_Rect tileRect = {tileRects[i].x, tileRects[i].y,
                             tileRects[i].w, tileRects[i].h};

        if (SDL_IntersectRect(&m_collBox, &tileRect, &intersect) == SDL_TRUE){
            if (m_yvel <= 0.0f){
                m_y = m_y + intersect.h;
                m_collBox.y = (int)m_y;
            }

            else if (m_yvel >= 0.0f){
                m_yvel = 0.0f;
                isJumping = false;
                m_y = m_y - intersect.h;
                m_collBox.y = (int)m_y;
            }
        }
    }

    if (m_x <= level.getLevelEnd().x && m_y <= level.getLevelEnd().y){
        std::cout << "YOU HAVE WON ADVENTURER!!!" << std::endl;
    }
}

void Mario::render(SDL_Renderer* renderer)
{
    m_animations[m_currentAnimation]->render((int)m_x, (int)m_y, renderer);
}