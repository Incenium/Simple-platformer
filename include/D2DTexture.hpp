/*
===============================================================================
* File: D2DTexture.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: SDL_Texture wrapper
===============================================================================
*/

#ifndef D2D_TEXTURE_HPP
#define D2D_TEXTURE_HPP

#include <string>

#include "D2DLogger.hpp"

typedef struct SDL_Renderer SDL_Renderer;
typedef struct SDL_Texture SDL_Texture;
typedef struct SDL_Rect SDL_Rect;

class D2DTexture {
  public:
    D2DTexture();
    ~D2DTexture();

    bool loadFromFile(std::string path, SDL_Renderer* renderer);

    void free();

    void render(int x, int y, SDL_Renderer* renderer,
                SDL_Rect* clip = nullptr);

    //SDL_Texture* getTexture();
    int getWidth();
    int getHeight();

  private:
    SDL_Texture* m_texture;

    int m_width;
    int m_height;

    D2DLogger logger;
};

#endif