#pragma once
#include <chrono>

struct FAstralClock {
public:
    FAstralClock();
    
    void Restart();
    float GetElapsedTime();
private:
    std::chrono::steady_clock::time_point ClockStart;
    std::chrono::steady_clock::time_point ClockLastPoint;
};
