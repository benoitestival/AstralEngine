#pragma once
#include <string>

#include "../../Utils/Delegate.h"

struct FTimerHandle {
public:
    int TimerId = -1;
    float InitialTimerLenght = 0.0f;

    static FTimerHandle Invalid();
    static FTimerHandle GenerateHandle(int BaseIndex);
};

template <>
struct std::hash<FTimerHandle>{
    std::size_t operator()(const FTimerHandle Handle) const noexcept {
        return std::hash<int>()(Handle.TimerId);
    }
};

DECLARE_DELEGATE(FTimerDelegate)

struct FTimer {
public:
    FTimer() = default;
    FTimer(const FTimerHandle& Handle, const FTimerDelegate& CallBack, bool ShouldLoop = false);
    bool operator==(const FTimerHandle& Handle) const;
    
    void SubstractTime(float Time);
    
    bool IsPaused() const;
    bool IsFinished() const;

    void BroadCast();
public:
    bool Loop = false;
    bool Paused = false;
    float RemainingTimerLenght = 0.0f;
private:
    FTimerHandle TimerHandle;
    FTimerDelegate TimerCallBack;
};
