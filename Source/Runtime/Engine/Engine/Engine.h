#pragma once
#include "../CoreObjects/Objects/BaseObject.h"
#include "../Time/AstralClock.h"

class AWindow;
class AWorld;
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
    virtual void Tick(float DeltaTime);
    virtual void End();

    float CalculateDeltaSeconds();

    AWindow* GetActiveWindow();
    
    AInputManager* GetInputManager();
    ARenderManager* GetRenderManager();
    ATimerManager* GetTimerManager();
    
    AWorld* GetActiveWorld();

    float GetDeltaTime() const;
protected:
    FAstralClock EngineClock;
    float EngineDeltaTime = 0.0f;

    AWindow* ActiveWindow = nullptr;
    
    AInputManager* InputManager = nullptr;
    ARenderManager* RenderManager = nullptr;
    ATimerManager* TimerManager = nullptr;
    
    AWorld* ActiveWorld = nullptr;
};
