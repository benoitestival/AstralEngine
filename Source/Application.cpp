#include "Application.h"
#include "Runtime/Configs/AstralEngineStatics.h"
#include "Runtime/Configs/ConfigUtils.h"
#include "Runtime/Core/Systems/ObjectManager.h"
#include "Runtime/Engine/Engine.h"

void Application::Start() {
    AstralEngineStatics::LoadStaticsUtils();
    
    Engine = AObjectManager::Get()->InstanciateNewObject<AEngine>(ConfigUtils::GetEngineClass(), nullptr);
    Engine->OnEngineStop.Bind(this, &Application::End);
    
    Engine->Start();
}

void Application::End() {
    delete Engine;
    Engine = nullptr;

    //TODO delete all managers
    
    AstralEngineStatics::ClearStaticsUtils();
}
