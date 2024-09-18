#pragma once
#include "../CoreObjects/Managers/Manager.h"
#include "../CoreObjects/Objects/BaseObject.h"
#include "../Time/AstralClock.h"

class AManager;
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
    template<class T = AManager>
    T* GetManager() {
        AManager* Object = nullptr;
        for (auto Manager : EngineManagers) {
            if (T::StaticClass() == Manager->GetClass() || Manager->IsChildOf(T::StaticClass())) {
                Object = Manager;
            }
        }
        return Cast<T>(Object);
    }
    
    AInputManager* GetInputManager();
    ARenderManager* GetRenderManager();
    ATimerManager* GetTimerManager();
    
    AWorld* GetActiveWorld();

    float GetDeltaTime() const;
protected:
    FAstralClock EngineClock;
    float EngineDeltaTime = 0.0f;

    AWindow* ActiveWindow = nullptr;
    TArray<AManager*> EngineManagers;
    
    AWorld* ActiveWorld = nullptr;
};
