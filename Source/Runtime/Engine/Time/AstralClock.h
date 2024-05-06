#pragma once

struct FAstralClock {
public:
    FAstralClock();
    
    void Restart();
    float GetElapsedTime();
private:
    float Time = 0.0f;
};
