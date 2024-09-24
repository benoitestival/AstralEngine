#include "AstralClock.h"

#include <chrono>

FAstralClock::FAstralClock() : ClockStart(std::chrono::steady_clock::now()), ClockLastPoint(std::chrono::steady_clock::now()){
}

void FAstralClock::Restart() {
    ClockStart = std::chrono::steady_clock::now();
    ClockLastPoint = std::chrono::steady_clock::now();
}

float FAstralClock::GetElapsedTime() {
    std::chrono::steady_clock::time_point ClockNow = std::chrono::steady_clock::now();
    std::chrono::duration<float> ElapsedTime = ClockNow - ClockLastPoint;
    ClockLastPoint = ClockNow;
    return ElapsedTime.count();
}
