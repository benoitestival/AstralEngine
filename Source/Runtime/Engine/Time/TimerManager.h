#pragma once
#include <chrono>

#include "AstralClock.h"
#include "TimerHandle.h"
#include "../CoreObjects/Objects/BaseObject.h"

DECLARE_DELEGATE(FTimerDelegate)

class ATimerManager : public ABaseObject{
public:
    ATimerManager();
    DECLARE_ASTRAL_ENGINE_CLASS(ATimerManager, ABaseObject)

    void Tick(float DeltaTime);
    virtual void Initialize() override;

    FTimerHandle RegisterHandle(FTimerDelegate& Delegate);
    void UnregisterHandle(FTimerHandle& Handle);
    
private:
    std::unordered_map<FTimerHandle, FTimerDelegate> RegistredTimers;
};
