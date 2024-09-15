#include "AstralEngine.h"

#include "../../../Window/Window.h"
#include "../../Inputs/Systems/InpuManager.h"
#include "../../Time/TimerManager.h"
#include "../../World/World.h"
#include "../../../Render/Systems/RenderManager.h"



void AstralEngine::Start() {
    AEngine::Start();

    GetActiveWindow()->Construct();
    
    GetInputManager()->Init();
    //TODO init otther core system
}

void AstralEngine::GuardedLoop() {
    while (GetActiveWindow()->IsOpen()) {
        Tick(CalculateDeltaSeconds());
    }
}

void AstralEngine::Tick(float DeltaTime) {
    AEngine::Tick(DeltaTime);

    GetInputManager()->HandleInputsEvents();

    GetTimerManager()->Tick(DeltaTime);
    GetActiveWorld()->Tick(DeltaTime);

    GetRenderManager()->Draw();
}

void AstralEngine::End() {

    GetActiveWindow()->Close();
    
    AEngine::End();
}
