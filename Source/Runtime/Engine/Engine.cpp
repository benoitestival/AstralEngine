#include "Engine.h"

void AEngine::Start() {
    
}

void AEngine::Run() {
}

void AEngine::End() {
    OnEngineStop.BroadCast();
}
