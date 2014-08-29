#include "SDL2/SDL_mixer.h"

#include "D2DError.hpp"
#include "D2DSoundEffect.hpp"

D2DSoundEffect::D2DSoundEffect()
{
    m_soundEffect = nullptr;

    logger.open();
}

D2DSoundEffect::~D2DSoundEffect()
{
    Mix_FreeChunk(m_soundEffect);
    
    m_soundEffect = nullptr;
}

void D2DSoundEffect::loadFromFile(std::string path)
{
    m_soundEffect = Mix_LoadWAV(path.c_str());
    if (m_soundEffect == nullptr){
        D2DWriteErrorContexts(logger);

        logger.write("Unable to load sound effect %s! SDL_mixer error: %s",
                     path.c_str(), Mix_GetError());

        exit(EXIT_FAILURE);
    }
}

void D2DSoundEffect::play(int numRepeats)
{
    Mix_PlayChannel(-1, m_soundEffect, numRepeats);
}