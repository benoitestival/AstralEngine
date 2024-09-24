#pragma once
#include "../Engine.h"

class ADebugTick;
class ADebugMain;

class AstralEngine : public AEngine {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AstralEngine, AEngine)

    virtual void Start() override;
    void GuardedLoop();
   
    virtual void Tick(float DeltaTime) override;
    virtual void End() override;
#if IS_DEBUG
private:
    ADebugMain* DebugMain = nullptr;
    ADebugTick* DebugTick = nullptr;
#endif
    
};
