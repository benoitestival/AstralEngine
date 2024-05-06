#include "InputComponent.h"

#include "../../Statics/GameplayStatics.h"
#include "../Objects/InputAction.h"
#include "../Objects/Modifiers/InputModifier.h"
#include "../Objects/Triggers/InputTrigger.h"
#include "../Systems/InpuManager.h"

void AInputComponent::RegisterAction(EKey Key, AInputAction* Action) {
    if (RegistredActions.contains(Key)) {
        RegistredActions.at(Key).push_back(Action);
    }
    else {
        TArray<AInputAction*> Actions = {Action};
        RegistredActions.insert(std::make_pair(Key, Actions));
    }
}

void AInputComponent::UnRegisterActionFromAllKeys(AInputAction* Action) {
    for (auto Key : GetAllMappedKeys()) {
        if (RegistredActions.at(Key).Contains(Action)) {
            RegistredActions.at(Key).Remove(Action);
        }
    }
}

void AInputComponent::UnRegisterActionForKey(AInputAction* Action, EKey Key) {
    if (RegistredActions.contains(Key)) {
        RegistredActions.at(Key).Remove(Action);
    }
}

bool AInputComponent::ShouldExecuteAction(EKey Key, EInputState KeyState) const {
    bool CanExecuteAction = true;
    if (!RegistredActions.contains(Key)) {
        CanExecuteAction = false;
    }
    else {
        TArray<AInputAction*> RegistredActionsForInput = RegistredActions.at(Key);
        bool CanTrigger = true;
        for (auto Action : RegistredActionsForInput) {
            if (CanTrigger) {
                TArray<AInputTrigger*> TriggerCondtions = Action->GetTriggerConditions().at(Key);
                for (auto TriggerCondition : TriggerCondtions) {
                    CanTrigger = TriggerCondition->CanTrigger(Key, KeyState);
                    if (!CanTrigger) {
                        break;
                    }
                }
            }
        }
    }
    return CanExecuteAction;
}

void AInputComponent::ExecuteAction(EKey Key, EInputState KeyState) {
    TArray<AInputAction*> RegistredActionsForInput = RegistredActions.at(Key);
    for (auto Action : RegistredActionsForInput) {
        FInputValue InputValue = FInputValue(Action->GetDesiredValueType(), KeyState);
        TArray<AInputModifier*> InputModifers = Action->GetInputModifiers().at(Key);
        for (auto InputModifer : InputModifers) {
            InputValue = InputModifer->ModifyValue(InputValue);
        }

        EInputState PreviousInputState = GetInputManager()->GetPreviousInputState(Key);
        if (KeyState == EInputState::Pressed && PreviousInputState == EInputState::Released) {
            Action->OnInputStart.BroadCast(InputValue);
        }

        if (KeyState == EInputState::Pressed) {
            Action->OnInputTrigger.BroadCast(InputValue);
        }

        if (KeyState == EInputState::Released && PreviousInputState == EInputState::Pressed) {
            Action->OnInputStop.BroadCast(InputValue);
        }
    }
}

AInputManager* AInputComponent::GetInputManager() {
    return GameplayStatics::GetInputManager();
}

TArray<EKey> AInputComponent::GetAllMappedKeys() {
    TArray<EKey> Keys = {};
    for (auto& Pair : RegistredActions) {
        Keys.push_back(Pair.first);
    }
    return Keys;
}
