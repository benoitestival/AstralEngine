#pragma once
#include "../../Runtime/Engine/CoreObjects/Objects/BaseObject.h"

class ADebugTick : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ADebugTick, ABaseObject)

    void DebugTick(float DeltaTime);
};
