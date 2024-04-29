#include "GameplayStatics.h"

#include "../../Application.h"
#include "../Engine/Engine.h"


AEngine* GameplayStatics::GetEngine() {
    return AstralEngineStatics::GetApp()->GetEngine();
}

AInpuManager* GameplayStatics::GetInputManager() {
    return GameplayStatics::GetEngine()->GetInputManager();
}

ARenderManager* GameplayStatics::GetRenderManager() {
    return GameplayStatics::GetEngine()->GetRenderManager();
}
