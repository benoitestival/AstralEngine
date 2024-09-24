#include "AstralEngine.h"

#include <iostream>

#include "../../../../Editor/Tests/DebugMain.h"
#include "../../../../Editor/Tests/DebugTick.h"
#include "../../../Window/Window.h"
#include "../../Inputs/Systems/InpuManager.h"
#include "../../Time/TimerManager.h"
#include "../../World/World.h"
#include "../../../Render/Systems/RenderManager.h"
#include "../../CoreObjects/ObjectManager.h"
#include "../../CoreObjects/Utils/ObjectCoreUtility.h"


void AstralEngine::Start() {
    AEngine::Start();

    GetActiveWindow()->Construct();
    SetShowMouseCursor(false);//By default the cursor is hidden, its depending of the scene or the controller to change it
    
    for (auto Manager : EngineManagers) {
        Manager->Init();
    }
    
    bool START_ENGINE_LOOP = true;
#if IS_DEBUG
    DebugMain = NewObject<ADebugMain>(ADebugMain::StaticClass());
    DebugTick = NewObject<ADebugTick>(ADebugTick::StaticClass());
    if (DebugMain->DebugMain() == EXIT_CODE) {
        START_ENGINE_LOOP = false;
    }
#endif

    if (START_ENGINE_LOOP) {
        GuardedLoop();
    }
    else {
        End();
    }
}

void AstralEngine::GuardedLoop() {
    while (GetActiveWindow()->IsOpen()) {
        Tick(CalculateDeltaSeconds());
    }
    End();
}

void AstralEngine::Tick(float DeltaTime) {
    AEngine::Tick(DeltaTime);
#if IS_DEBUG
    DebugTick->DebugTick(DeltaTime);
#endif
    
    GetInputManager()->HandleInputsEvents(DeltaTime);
    GetTimerManager()->Tick(DeltaTime);

    GetRenderManager()->Draw();
}

void AstralEngine::End() {
    GetActiveWindow()->Close();
    AObjectManager::Get()->ClearLivingObjects();
    
    AEngine::End();
}
