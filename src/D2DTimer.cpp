#include "D2DTimer.hpp"

D2DTimer::D2DTimer()
{
    m_startTicks = 0;
    m_pausedTicks = 0;

    m_paused = false;
    m_started = false;
}

void D2DTimer::start()
{
    m_started = true;
    m_paused = false;

    m_startTicks = SDL_GetTicks();
    m_pausedTicks = 0;
}

void D2DTimer::stop()
{
    m_started = false;
    m_paused = true;

    m_startTicks = 0;
    m_pausedTicks = 0;
}

void D2DTimer::pause()
{
    if (m_started && !m_paused){
        m_paused = true;

        m_pausedTicks = SDL_GetTicks() - m_startTicks;
        m_startTicks = 0;
    }
}

void D2DTimer::unpause()
{
    if (m_started && m_paused){
        m_paused = false;

        m_startTicks = SDL_GetTicks() - m_pausedTicks;
        m_pausedTicks = 0;
    }
}

Uint32 D2DTimer::getTicks()
{
    Uint32 time = 0;

    if (m_started){
        if (m_paused){
            time = m_pausedTicks;
        }

        else {
            time = SDL_GetTicks() - m_startTicks;
        }
    }

    return time;
}

bool D2DTimer::isStarted()
{
    return m_started;
}

bool D2DTimer::isPaused()
{
    return m_paused && m_started;
}