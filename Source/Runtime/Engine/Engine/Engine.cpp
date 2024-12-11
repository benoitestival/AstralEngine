#include "Engine.h"

#include <iostream>

#include "../../../Application.h"
#include "../../Configs/ConfigUtils.h"
#include "../../Render/Systems/RenderManager.h"
#include "../../Window/Window.h"
#include "../CoreObjects/ObjectManager.h"
#include "../CoreObjects/Utils/ObjectCoreUtility.h"
#include "../Inputs/Systems/InpuManager.h"
#include "../Time/TimerManager.h"


void AEngine::Start() {
    ActiveWindow = NewObject<AWindow>(ConfigUtils::GetWindowClass());
    
    EngineManagers.Add(NewObject<AInputManager>(ConfigUtils::GetInputManagerClass()));
    EngineManagers.Add(NewObject<ARenderManager>(ConfigUtils::GetRenderManagerClass()));
    EngineManagers.Add(NewObject<ATimerManager>(ATimerManager::StaticClass()));
    
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
    return GetManager<AInputManager>();
}

ARenderManager* AEngine::GetRenderManager() {
    return GetManager<ARenderManager>();
}

ATimerManager* AEngine::GetTimerManager() {
    return GetManager<ATimerManager>();
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
