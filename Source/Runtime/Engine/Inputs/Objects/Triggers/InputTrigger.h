#pragma once
#include "../InputAction.h"

class AInputTrigger : public AInputAction {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInputTrigger, AInputAction)

    virtual bool CanTrigger(EKey Key, EInputState State){return true;};
};
