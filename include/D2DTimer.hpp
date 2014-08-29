/*
===============================================================================
* File: D2DTimer.hpp
*
* Author: Andrew Killian
*
* Email: Inceniium@gmail.com
*
* Description: D2DTimer class
===============================================================================
*/

#ifndef D2D_TIMER_HPP
#define D2D_TIMER_HPP

#include "SDL2/SDL.h"

//extern std::ofstream DEBUG_LOG;

class D2DTimer {
  public:
    D2DTimer();

    void start();
    void stop();
    void pause();
    void unpause();

    Uint32 getTicks();

    bool isStarted();
    bool isPaused();

  private:
    Uint32 m_startTicks;
    Uint32 m_pausedTicks;

    bool m_paused;
    bool m_started;
};

#endif