#include "Application.h"
#include "Runtime/Configs/AstralEngineStatics.h"
#include "Runtime/Configs/ConfigUtils.h"
#include "Runtime/Engine/CoreObjects/ObjectManager.h"
#include "Runtime/Engine/CoreObjects/Utils/ObjectCoreUtility.h"
#include "Runtime/Engine/Engine/Engine.h"

void Application::Start() {
    AstralEngineStatics::InitAstralEngineStatics(this);
    
    Engine = NewObject<AEngine>(ConfigUtils::GetEngineClass(), nullptr);
    
    Engine->Start();
}

void Application::End() {
    
    AObjectManager::Get()->Clear();
    delete Engine;
    Engine = nullptr;
    
    AstralEngineStatics::ClearAstralEngineStatics();
}

void Application::Terminate() {
    //TODO check that the engine is realy in exit mode to avoid leaking any memory
    AstralEngineStatics::GetApp()->End();
}

AEngine* Application::GetEngine() {
    return Engine;
}
