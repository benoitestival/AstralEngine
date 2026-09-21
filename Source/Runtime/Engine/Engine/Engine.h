#pragma once
#include "../CoreObjects/Systems/EngineSystem.h"
#include "../CoreObjects/Objects/BaseObject.h"
#include "../Time/AstralClock.h"

class ARenderer;
class AWindow;
class AWorld;
class ATimerManager;
class ARenderManager;
class AInputManager;

class AEngine : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AEngine, ABaseObject)
    
    DECLARE_DELEGATE(FOnEngineStop)
    FOnEngineStop OnEngineStop;
    
    virtual void Start();
    virtual void Tick(float DeltaTime);
    virtual void End();

    float CalculateDeltaSeconds();

    AWindow* GetActiveWindow();
    template<class T = AEngineSystem>
    T* GetEngineSystem() {
        AEngineSystem* Object = nullptr;
        for (auto System : EngineSystems) {
            if (T::StaticClass() == System->GetClass() || System->IsChildOf(T::StaticClass())) {
                Object = System;
            }
        }
        return Cast<T>(Object);
    }
    
    AInputManager* GetInputManager();
    ARenderer* GetRenderManager();
    ATimerManager* GetTimerManager();
    
    AWorld* GetActiveWorld();

    float GetDeltaTime() const;
#if IS_DEBUG
    int FrameCount;
#endif

    void SetShowMouseCursor(bool CursorVisibility);
    bool GetShowMouseCursor() const; 
protected:
    FAstralClock EngineClock;
    float EngineDeltaTime = 0.0f;

    AWindow* ActiveWindow = nullptr;
    TArray<AEngineSystem*> EngineSystems;
    
    AWorld* ActiveWorld = nullptr;

    bool ShowMouseCursor = false;
};
