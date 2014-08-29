/*
===============================================================================
* File: D2DMusic.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: Mix_Music wrapper
===============================================================================
*/

#ifndef D2D_MUSIC_HPP
#define D2D_MUSIC_HPP

#include <string>

#include "D2DLogger.hpp"

typedef struct _Mix_Music Mix_Music;

class D2DMusic {
  public:
    D2DMusic();
    ~D2DMusic();

    void loadFromFile(std::string path);

    void play();
    //void pause();
    //void resume();
    void stop();

    // Add stuff like fade out
  private:
    Mix_Music* m_music;

    D2DLogger logger;
};

#endif