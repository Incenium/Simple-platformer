#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "D2DError.hpp"

#include "D2DTexture.hpp"

D2DTexture::D2DTexture()
{
    m_texture = nullptr;

    m_width = 0;
    m_height = 0;

    logger.open();
}

D2DTexture::~D2DTexture()
{
    free();
}

bool D2DTexture::loadFromFile(std::string path, SDL_Renderer* renderer)
{
    free();

    SDL_Texture* newTexture = nullptr;

    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr){
        D2DWriteErrorContexts(logger);

        logger.write("Unable to load texture %s!, SDL_image error: %s\n",
                     path.c_str(), IMG_GetError());

        exit(EXIT_FAILURE);
    }

    newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

    if (newTexture == nullptr){
        D2DWriteErrorContexts(logger);

        logger.write("Unable to create texture from %s! SDL error: %s\n",
                     path.c_str(), SDL_GetError());
        
        exit(EXIT_FAILURE);
    }

    m_width = loadedSurface->w;
    m_height = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    m_texture = newTexture;

    return m_texture != nullptr;
}

void D2DTexture::free()
{
    if (m_texture != nullptr){
        SDL_DestroyTexture(m_texture);

        m_width = 0;
        m_height = 0;
    }
}

void D2DTexture::render(int x, int y, SDL_Renderer* renderer, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, m_width, m_height};

    if (clip != nullptr){
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(renderer, m_texture, clip, &renderQuad);
}

int D2DTexture::getWidth()
{
    return m_width;
}

int D2DTexture::getHeight()
{
    return m_height;
}