#include "InputComponent.h"

#include "../../Statics/GameplayStatics.h"
#include "../Objects/InputAction.h"
#include "../Objects/Modifiers/InputModifier.h"
#include "../Objects/Triggers/InputTrigger.h"
#include "../Systems/InpuManager.h"

void AInputComponent::RegisterAction(EKey Key, AInputAction* Action) {
    if (RegistredActions.Contains(Key)) {
        RegistredActions.Find(Key).Add(Action);
    }
    else {
        TArray<AInputAction*> Actions = {Action};
        RegistredActions.Insert(std::make_pair(Key, Actions));
    }
}

void AInputComponent::UnRegisterActionFromAllKeys(AInputAction* Action) {
    for (auto Key : GetAllMappedKeys()) {
        if (RegistredActions.Find(Key).Contains(Action)) {
            RegistredActions.Find(Key).Remove(Action);
        }
    }
}

void AInputComponent::UnRegisterActionForKey(AInputAction* Action, EKey Key) {
    if (RegistredActions.Contains(Key)) {
        RegistredActions.Find(Key).Remove(Action);
    }
}

bool AInputComponent::ShouldExecuteAction(EKey Key, FInputParams InputParams) const {
    bool CanExecuteAction = true;
    if (!RegistredActions.Contains(Key)) {
        CanExecuteAction = false;
    }
    else {
        TArray<AInputAction*> RegistredActionsForInput = RegistredActions.Find(Key);
        bool CanTrigger = true;
        for (auto Action : RegistredActionsForInput) {
            if (CanTrigger && Action->GetTriggerConditions().Contains(Key)) {
                TArray<AInputTrigger*> TriggerCondtions = Action->GetTriggerConditions().Find(Key);
                for (auto TriggerCondition : TriggerCondtions) {
                    CanTrigger = TriggerCondition->CanTrigger(Key, InputParams.InputState);
                    if (!CanTrigger) {
                        CanExecuteAction = false;
                        break;
                    }
                }
            }
        }
    }
    return CanExecuteAction;
}

void AInputComponent::ExecuteAction(EKey Key, FInputParams InputParams) {
    TArray<AInputAction*> RegistredActionsForInput = RegistredActions.Find(Key);
    for (auto Action : RegistredActionsForInput) {
        FInputValue InputValue = FInputValue(Action->GetDesiredValueType(), InputParams);

        if (Action->GetInputModifiers().Contains(Key)) {
            TArray<AInputModifier*> InputModifers = Action->GetInputModifiers().Find(Key);
            for (auto InputModifer : InputModifers) {
                InputValue = InputModifer->ModifyValue(InputValue);
            }
        }

        EInputState PreviousInputState = GetInputManager()->GetPreviousInputState(Key);
        if (InputUtils::IsInputActive(InputParams.InputState) && InputUtils::IsInputInactive(PreviousInputState)) {
            Action->OnInputStart.BroadCast(InputValue);
        }

        if (InputUtils::IsInputActive(InputParams.InputState)) {
            Action->OnInputTrigger.BroadCast(InputValue);
        }

        if (InputUtils::IsInputInactive(InputParams.InputState) && InputUtils::IsInputActive(PreviousInputState)) {
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
        Keys.Add(Pair.first);
    }
    return Keys;
}
