#include "GameplayStatics.h"

#include "../../../Application.h"
#include "../Engine/Engine.h"


AEngine* GameplayStatics::GetEngine() {
    return AstralEngineStatics::GetApp()->GetEngine();
}

AInputManager* GameplayStatics::GetInputManager() {
    return GameplayStatics::GetEngine()->GetInputManager();
}

ARenderManager* GameplayStatics::GetRenderManager() {
    return GameplayStatics::GetEngine()->GetRenderManager();
}

ATimerManager* GameplayStatics::GetTimerManager() {
    return GameplayStatics::GetEngine()->GetTimerManager();
}

float GameplayStatics::GetDeltaTime() {
    return GameplayStatics::GetEngine()->GetDeltaTime();
}

void GameplayStatics::SetShowMouseCursor(bool CursorVisibility) {
    GetEngine()->SetShowMouseCursor(CursorVisibility);
}

bool GameplayStatics::ShowMouseCursor() {
    return GetEngine()->GetShowMouseCursor();
}
