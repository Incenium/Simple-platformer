#include "SDL2/SDL_mixer.h"

#include "D2DError.hpp"
#include "D2DMusic.hpp"

D2DMusic::D2DMusic()
{
    m_music = nullptr;

    logger.open();
}

D2DMusic::~D2DMusic()
{
    Mix_FreeMusic(m_music);

    m_music = nullptr;
}

void D2DMusic::loadFromFile(std::string path)
{
    m_music = Mix_LoadMUS(path.c_str());
    if (m_music == nullptr){
        D2DWriteErrorContexts(logger);

        logger.write("Unable to load music %s! SDL_mixer error: %s\n",
                     path.c_str(), Mix_GetError());

        exit(EXIT_FAILURE);
    }
}

// Might want to add a feature to add if we want repeat or not
void D2DMusic::play()
{
    if (Mix_PlayingMusic() == 0){
        Mix_PlayMusic(m_music, -1);
    }

    else {
        if (Mix_PausedMusic() == 1){
            Mix_ResumeMusic();
        }

        else {
            Mix_PauseMusic();
        }
    }
}

void D2DMusic::stop()
{
    Mix_HaltMusic();
}