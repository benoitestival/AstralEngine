#include "AstralEngine.h"

#include "../../../../Editor/Tests/DebugMain.h"
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

    for (auto Manager : EngineManagers) {
        Manager->Init();
    }
    
    bool START_ENGINE_LOOP = true;
#if IS_DEBUG
    ADebugMain* DebugMain = NewObject<ADebugMain>(ADebugMain::StaticClass());
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

    GetInputManager()->HandleInputsEvents();
    GetTimerManager()->Tick(DeltaTime);

    GetRenderManager()->Draw();
}

void AstralEngine::End() {
    GetActiveWindow()->Close();
    AObjectManager::Get()->ClearLivingObjects();
    
    AEngine::End();
}
