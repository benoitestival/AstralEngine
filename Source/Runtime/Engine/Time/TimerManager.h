#pragma once
#include <chrono>

#include "AstralClock.h"
#include "TimerHandle.h"
#include "../CoreObjects/Objects/BaseObject.h"




class ATimerManager : public ABaseObject{
public:
    ATimerManager();
    DECLARE_ASTRAL_ENGINE_CLASS(ATimerManager, ABaseObject)

    void Tick(float DeltaTime);
    virtual void Initialize() override;

    FTimerHandle RegisterTimer(const FTimerDelegate& Delegate, float TimerLenght = 1.0f, bool Loop = false);
    FTimerHandle RegisterTimerUntilNextTick(const FTimerDelegate& Delegate);
    void UnregisterTimer(FTimerHandle& Handle);
    
private:
    TArray<FTimer> RegistredTimers;
};
