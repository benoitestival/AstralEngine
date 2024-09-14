#pragma once
#include "../Engine.h"

class AstralEngine : public AEngine {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AstralEngine, AEngine)

    virtual void Start() override;
    void GuardedLoop();
   
    virtual void Tick(float DeltaTime) override;
    virtual void End() override;
};
