#include "Engine.h"

#include "../Configs/ConfigUtils.h"
#include "../Core/Systems/ObjectManager.h"

void AEngine::Start() {
    InputManager = AObjectManager::Get()->InstanciateNewObject<AInpuManager>(ConfigUtils::GetInputManagerClass());
}

void AEngine::Run() {
}

void AEngine::End() {
    OnEngineStop.BroadCast();
}

AInpuManager* AEngine::GetInputManager() {
    return InputManager;
}
