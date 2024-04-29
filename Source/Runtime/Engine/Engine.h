#pragma once
#include "../CoreObjects/Objects/BaseObject.h"

class ARenderManager;
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
    ARenderManager* GetRenderManager();
protected:

    AInpuManager* InputManager = nullptr;
    ARenderManager* RenderManager = nullptr;
};
