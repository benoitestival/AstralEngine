#include "AstralClock.h"

#include <chrono>

FAstralClock::FAstralClock() : Time(std::chrono std::chrono::steady_clock::now()){
}

void FAstralClock::Restart() {
}

float FAstralClock::GetElapsedTime() {
}
