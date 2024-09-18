#pragma once
#include "../Objects/BaseObject.h"

class AManager : public ABaseObject {
public:
    AManager() = default;
    DECLARE_ASTRAL_ENGINE_CLASS(AManager, ABaseObject)

    virtual void Init();
    
};
