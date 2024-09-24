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

void AInputManager::HandleInputsEvents(float DeltaTime) {
    //tick function for inputs
}

void AInputManager::HandleKeyInput(EKey Key, FInputParams InputParams) {
    for(auto InputComponent : RegistredComponents.Find(Key)) {
        if (InputComponent != nullptr) {
            if (InputComponent->ShouldExecuteAction(Key, InputParams)) {
                InputComponent->ExecuteAction(Key, InputParams);
            }
        }
    }
    //Key Handle finish
    if (PreviousInputState.Contains(Key)) {
        PreviousInputState.Find(Key) = InputParams.InputState;
    }
    else {
        PreviousInputState.Insert(std::make_pair(Key, InputParams.InputState));
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
    return {0.0f};
}

void AInputManager::SetCursorPosition(const FVector2D& Pos) {
}
