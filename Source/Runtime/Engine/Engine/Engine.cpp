#include "Engine.h"

#include "../../Configs/ConfigUtils.h"
#include "../../Window/Window.h"
#include "../CoreObjects/ObjectManager.h"
#include "../Time/TimerManager.h"


void AEngine::Start() {
    ActiveWindow = AObjectManager::Get()->InstanciateNewObject<AWindow>(ConfigUtils::GetWindowClass());

    InputManager = AObjectManager::Get()->InstanciateNewObject<AInputManager>(ConfigUtils::GetInputManagerClass());
    RenderManager = AObjectManager::Get()->InstanciateNewObject<ARenderManager>(ConfigUtils::GetRenderManagerClass());
    
    TimerManager = AObjectManager::Get()->InstanciateNewObject<ATimerManager>(ATimerManager::StaticClass());
    EngineClock = FAstralClock();
}

void AEngine::Tick(float DeltaTime) {
}


void AEngine::End() {
    OnEngineStop.BroadCast();
}

float AEngine::CalculateDeltaSeconds() {
    EngineDeltaTime = EngineClock.GetElapsedTime();
    return EngineDeltaTime;
}

AInputManager* AEngine::GetInputManager() {
    return InputManager;
}

ARenderManager* AEngine::GetRenderManager() {
    return RenderManager;
}

ATimerManager* AEngine::GetTimerManager() {
    return TimerManager;
}

AWindow* AEngine::GetActiveWindow() {
    return ActiveWindow;
}

AWorld* AEngine::GetActiveWorld() {
    return ActiveWorld;
}

float AEngine::GetDeltaTime() const {
    return EngineDeltaTime;
}
