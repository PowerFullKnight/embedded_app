#ifndef FPS_H
#define FPS_H

#include <chrono>

class Fps
{
public:
    Fps();

    // Return true if one second is elapsed
    bool update();

    unsigned int getFps() const;

    void disableFramerateLimit();
    void setFramerateLimit(unsigned fps);
    bool isFramerateLimitEnabled() const;

protected:

    unsigned int m_frame;
    unsigned int m_fps;

    typedef std::chrono::steady_clock clock;
    clock::time_point m_t0;
    clock::time_point m_t1;

    constexpr static clock::duration dtn = std::chrono::duration<int>(1); // 1 second

    bool m_isFpsLimitEnabled;
    std::chrono::nanoseconds m_minFrameDuration;
    clock::time_point m_lastFrameTime;
};

#endif // FPS_H
