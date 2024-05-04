#pragma once
#include "../CoreObjects/Objects/BaseObject.h"

class ATimerManager;
class ARenderManager;
class AInputManager;

class AEngine : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AEngine, ABaseObject)
public:

    DECLARE_DELEGATE(FOnEngineStop)
    FOnEngineStop OnEngineStop;
    
    virtual void Start();
    virtual void Run();
    virtual void End();

    float CalculateDeltaSeconds();
    
    AInputManager* GetInputManager();
    ARenderManager* GetRenderManager();
    ATimerManager* GetTimerManager();

    float GetDeltaTime() const;
protected:

    float EngineDeltaTime = 0.0f;
    AInputManager* InputManager = nullptr;
    ARenderManager* RenderManager = nullptr;
    ATimerManager* TimerManager = nullptr;
};
