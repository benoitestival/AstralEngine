#include "Application.h"
#include "Runtime/Configs/ApplicationRegistries.h"
#include "Runtime/Configs/ConfigUtils.h"
#include "Runtime/Core/Systems/ObjectManager.h"
#include "Runtime/Engine/Engine.h"

void Application::Start() {
    ApplicationRegistries::FillRegistries();
    Engine = AObjectManager::Get()->InstanciateNewObject<AEngine>(ConfigUtils::GetEngineClass(), nullptr);
    Engine->Start();
}

void Application::End() {
    ApplicationRegistries::ClearRegistries();
}
