#include "Engine.h"

#include <iostream>

#include "../../../Application.h"
#include "../../Configs/ConfigUtils.h"
#include "../../Render/RenderAPIs/Renderer.h"
#include "../../Window/Window.h"
#include "../CoreObjects/ObjectManager.h"
#include "../CoreObjects/Utils/ObjectCoreUtility.h"
#include "../Inputs/Systems/InpuManager.h"
#include "../Time/TimerManager.h"


void AEngine::Start() {
    ActiveWindow = NewObject<AWindow>(ConfigUtils::GetWindowClass());
    
    EngineSystems.Add(NewObject<AInputManager>(ConfigUtils::GetInputManagerClass()));
    EngineSystems.Add(NewObject<ARenderer>(ConfigUtils::GetRenderManagerClass()));
    EngineSystems.Add(NewObject<ATimerManager>(ATimerManager::StaticClass()));
    
    EngineClock = FAstralClock();
}

void AEngine::Tick(float DeltaTime) {
#if IS_DEBUG
    FrameCount++;
    //std::cout << FrameCount << std::endl;
#endif
}


void AEngine::End() {
    AObjectManager::Get()->ClearLivingObjects();
    AObjectManager::Get()->ClearManagers();
    
    OnEngineStop.BroadCast();
    
    Application::Terminate();
}

float AEngine::CalculateDeltaSeconds() {
    EngineDeltaTime = EngineClock.GetElapsedTime();
    return EngineDeltaTime;
}

AInputManager* AEngine::GetInputManager() {
    return GetEngineSystem<AInputManager>();
}

ARenderer* AEngine::GetRenderManager() {
    return GetEngineSystem<ARenderer>();
}

ATimerManager* AEngine::GetTimerManager() {
    return GetEngineSystem<ATimerManager>();
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

void AEngine::SetShowMouseCursor(bool CursorVisibility) {
    ShowMouseCursor = CursorVisibility;
    GetActiveWindow()->SetShowMouseCursor(ShowMouseCursor);
}

bool AEngine::GetShowMouseCursor() const {
    return ShowMouseCursor;
}
