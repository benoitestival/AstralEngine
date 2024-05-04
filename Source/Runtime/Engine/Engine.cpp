#include "Engine.h"

#include "../Configs/ConfigUtils.h"
#include "../CoreObjects/ObjectManager.h"


void AEngine::Start() {
    InputManager = AObjectManager::Get()->InstanciateNewObject<AInputManager>(ConfigUtils::GetInputManagerClass());
    RenderManager = AObjectManager::Get()->InstanciateNewObject<ARenderManager>(ConfigUtils::GetRenderManagerClass());
}

void AEngine::Run() {
}

void AEngine::End() {
    OnEngineStop.BroadCast();
}

AInputManager* AEngine::GetInputManager() {
    return InputManager;
}

ARenderManager* AEngine::GetRenderManager() {
    return RenderManager;
}

float AEngine::GetDeltaTime() const {
    return DeltaTime;
}
