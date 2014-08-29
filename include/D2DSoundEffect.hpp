/*
===============================================================================
* File: D2DSoundEffect.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Mix_chunk wrapper
===============================================================================
*/

#ifndef D2D_SOUND_EFFECT_HPP
#define D2D_SOUND_EFFECT_HPP

#include <string>

#include "D2DLogger.hpp"

typedef struct Mix_Chunk Mix_Chunk;

class D2DSoundEffect {
  public:
    D2DSoundEffect();
    ~D2DSoundEffect();

    void loadFromFile(std::string path);

    void play(int numRepeats);

  private:
    Mix_Chunk* m_soundEffect;

    D2DLogger logger;
};

#endif