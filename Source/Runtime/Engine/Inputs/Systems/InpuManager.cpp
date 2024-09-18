#include "InpuManager.h"

#include "../Components/InputComponent.h"
#include "../Objects/InputAction.h"

void AInputManager::Init() {
    for (auto Key : InputUtils::GetKeys()) {
        RegistredComponents.Insert(std::make_pair(Key, TArray<AInputComponent*>()));
    }
}

void AInputManager::RegisterInputComponent(AInputComponent* InputComponent) {
    for (auto& Key: InputComponent->GetAllMappedKeys()) {
        RegistredComponents.Find(Key).Add(InputComponent);
    }
}

void AInputManager::HandleInputsEvents() {
}

void AInputManager::HandleKeyInput(EKey Key, EInputState InputState) {
    for(auto InputComponent : RegistredComponents.Find(Key)) {
        if (InputComponent != nullptr) {
            if (InputComponent->ShouldExecuteAction(Key, InputState)) {
                InputComponent->ExecuteAction(Key, InputState);
            }
        }
    }
    //Key Handle finish
    if (PreviousInputState.Contains(Key)) {
        PreviousInputState.Find(Key) = InputState;
    }
    else {
        PreviousInputState.Insert(std::make_pair(Key, InputState));
    }
}

bool AInputManager::IsKeyPressed(EKey Key) const {
    return false;
}

EInputState AInputManager::GetPreviousInputState(EKey Key) {
    EInputState InputState = EInputState::Released;//by default is released in case it has never been pressed
    if (PreviousInputState.Contains(Key)) {
        InputState = PreviousInputState.Find(Key);
    }
    return InputState;
}

FVector2D AInputManager::GetCursorPosition() const {
    return CursorPosition;
}
