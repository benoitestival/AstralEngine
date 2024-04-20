#pragma once
#include "../Objects/BaseObject.h"

class AEngine : public ABaseObject{
public:
    AEngine();
    DECLARE_ASTRAL_ENGINE_CLASS(AEngine, ABaseObject)

    virtual void Start();
    virtual void Run();
    virtual void End();
};
