#include "Engine.h"

#include "../Configs/ConfigUtils.h"
#include "../CoreObjects/ObjectManager.h"
#include "Time/TimerManager.h"


void AEngine::Start() {
    InputManager = AObjectManager::Get()->InstanciateNewObject<AInputManager>(ConfigUtils::GetInputManagerClass());
    RenderManager = AObjectManager::Get()->InstanciateNewObject<ARenderManager>(ConfigUtils::GetRenderManagerClass());
    
    TimerManager = AObjectManager::Get()->InstanciateNewObject<ATimerManager>(ATimerManager::StaticClass());
}

void AEngine::Run() {
}

void AEngine::End() {
    OnEngineStop.BroadCast();
}

float AEngine::CalculateDeltaSeconds() {
    EngineDeltaTime = 0.0f;
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

float AEngine::GetDeltaTime() const {
    return EngineDeltaTime;
}
