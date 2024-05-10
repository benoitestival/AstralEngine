#include "TimerHandle.h"

FTimerHandle FTimerHandle::Invalid() {
    return {-1, -1.0f};
}

FTimerHandle FTimerHandle::GenerateHandle(int BaseIndex) {
    int HandleID = BaseIndex * std::rand();
    return {HandleID};
}

FTimer::FTimer(const FTimerHandle& Handle, const FTimerDelegate& CallBack, bool ShouldLoop) {
    TimerHandle = Handle;
    TimerCallBack = CallBack;
    Loop = ShouldLoop;

    RemainingTimerLenght = TimerHandle.InitialTimerLenght;
}

bool FTimer::operator==(const FTimerHandle& Handle) const {
    return Handle.TimerId == TimerHandle.TimerId;
}

void FTimer::SubstractTime(float Time) {
    RemainingTimerLenght = RemainingTimerLenght - Time;
}

bool FTimer::IsPaused() const {
    return Paused;
}

bool FTimer::IsFinished() const {
    return RemainingTimerLenght <= 0.0f;
}

void FTimer::BroadCast() {
    return TimerCallBack.BroadCast();
}
