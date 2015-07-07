#include "Fps.h"

#include <thread>

Fps::Fps():
    m_frame(0), m_fps(0), m_t0(), m_t1(),
    m_isFpsLimitEnabled(false), m_minFrameDuration(), m_lastFrameTime()
{
    m_t0 = clock::now();
}

bool Fps::update()
{
    bool oneSecondElapsed = false;

    ++m_frame;
    m_t1 = clock::now();
    if(m_t1 - std::chrono::duration<int>(1) >= m_t0)
    {
        m_fps = m_frame;

        m_t0 = clock::now();
        m_frame = 0;

        oneSecondElapsed = true;
    }

    if(m_isFpsLimitEnabled)
    {
        const auto now = clock::now();
        const std::chrono::nanoseconds frameDuration = now - m_lastFrameTime;
        if( frameDuration < m_minFrameDuration )
        {
            std::this_thread::sleep_for(m_minFrameDuration - frameDuration);
        }

        m_lastFrameTime = now;
    }


    return oneSecondElapsed;
}

unsigned int Fps::getFps() const
{
    return m_fps;
}

void Fps::disableFramerateLimit()
{
    m_isFpsLimitEnabled = false;
}

void Fps::setFramerateLimit(unsigned fps)
{
    m_isFpsLimitEnabled = true;
    m_minFrameDuration = std::chrono::nanoseconds(static_cast<long long int>(1e9 / fps));
}

bool Fps::isFramerateLimitEnabled() const
{
    return m_isFpsLimitEnabled;
}
