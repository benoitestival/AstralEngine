#include "TimerManager.h"

ATimerManager::ATimerManager() {
}


void ATimerManager::Tick(float DeltaTime) {
    for (auto& Timer : RegistredTimers) {
        if (!Timer.IsPaused()) {
            Timer.SubstractTime(DeltaTime);
            if (Timer.IsFinished()) {
                Timer.BroadCast();
            }
        }
    }
}


FTimerHandle ATimerManager::RegisterTimer(const FTimerDelegate& Delegate, float TimerLenght, bool Loop) {
    FTimerHandle TimerHandle = FTimerHandle::GenerateHandle(RegistredTimers.Lenght());
    TimerHandle.InitialTimerLenght = TimerLenght;
    
    if (!RegistredTimers.Contains(TimerHandle)) {
        FTimer Timer = FTimer(TimerHandle, Delegate, Loop);
        RegistredTimers.Add(Timer);
    }
    else {
        TimerHandle = FTimerHandle::Invalid();
    }
    return TimerHandle;
}

FTimerHandle ATimerManager::RegisterTimerUntilNextTick(const FTimerDelegate& Delegate) {
    return RegisterTimer(Delegate, 0.0f, false);
}

void ATimerManager::UnregisterTimer(FTimerHandle& Handle) {
    RegistredTimers.RemoveByKey(Handle);
}

