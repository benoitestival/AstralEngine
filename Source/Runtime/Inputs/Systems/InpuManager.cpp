#include "InpuManager.h"

#include "../Objects/InputAction.h"

void AInpuManager::Init() {
    for (auto Key : InputUtils::GetKeys()) {
        RegistredActions.insert(std::make_pair(Key, TArray<AInputAction*>()));
    }
}

void AInpuManager::HandleKeyboardInput(EKey Key, EKeyboardKeyState ActionType) {
    for(auto InputAction : RegistredActions.at(Key)) {
        if (InputAction != nullptr) {
            if (InputAction->ShouldExecuteKeyboardAction(Key, ActionType)) {
                InputAction->ExecuteKeyboardAction(Key, ActionType);
            }
        }
    }
}

bool AInpuManager::IsKeyPressed(EKey Key) const {
    return false;
}
