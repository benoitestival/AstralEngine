#include "InpuManager.h"

AInpuManager* AInpuManager::InputManager = nullptr;

AInpuManager::AInpuManager() {
}

AInpuManager::~AInpuManager() {
}

AInpuManager* AInpuManager::Get() {
    if (InputManager == nullptr) {
        InputManager = new AInpuManager();
    }
    return InputManager;
}
