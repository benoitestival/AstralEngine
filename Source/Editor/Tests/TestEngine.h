#pragma once
#include "../../Runtime/Engine/Engine/Engine.h"

class ATestEngine : AEngine{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ATestEngine, AEngine)

    void Start() override;
};
