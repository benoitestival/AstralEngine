#pragma once
#include "../Core/Objects/BaseObject.h"

class AInpuManager;

class AEngine : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AEngine, ABaseObject)
public:

    DECLARE_DELEGATE(FOnEngineStop)
    FOnEngineStop OnEngineStop;
    
    virtual void Start();
    virtual void Run();
    virtual void End();

    AInpuManager* GetInputManager();
protected:

    AInpuManager* InputManager = nullptr;
};
