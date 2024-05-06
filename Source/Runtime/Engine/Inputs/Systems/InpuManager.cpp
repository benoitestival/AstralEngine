#include "InpuManager.h"

#include "../Components/InputComponent.h"
#include "../Objects/InputAction.h"

void AInputManager::Init() {
    for (auto Key : InputUtils::GetKeys()) {
        RegistredComponents.insert(std::make_pair(Key, TArray<AInputComponent*>()));
    }
}

void AInputManager::HandleKeyInput(EKey Key, EInputState InputState) {
    for(auto InputComponent : RegistredComponents.at(Key)) {
        if (InputComponent != nullptr) {
            if (InputComponent->ShouldExecuteAction(Key, InputState)) {
                InputComponent->ExecuteAction(Key, InputState);
            }
        }
    }
    //Key Handle finish
    if (PreviousInputState.contains(Key)) {
        PreviousInputState.at(Key) = InputState;
    }
    else {
        PreviousInputState.insert(std::make_pair(Key, InputState));
    }
}

bool AInputManager::IsKeyPressed(EKey Key) const {
    return false;
}

EInputState AInputManager::GetPreviousInputState(EKey Key) {
    EInputState InputState = EInputState::Released;//by default is released in case it has never been pressed
    if (PreviousInputState.contains(Key)) {
        InputState = PreviousInputState.at(Key);
    }
    return InputState;
}
