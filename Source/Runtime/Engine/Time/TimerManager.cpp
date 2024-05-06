#include "TimerManager.h"

ATimerManager::ATimerManager() {
}
void ATimerManager::Initialize() {
    Super::Initialize();

}

void ATimerManager::Tick(float DeltaTime) {
}


FTimerHandle ATimerManager::RegisterHandle(FTimerDelegate& Delegate) {
    return {};
}

void ATimerManager::UnregisterHandle(FTimerHandle& Handle) {
}

