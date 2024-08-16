#include "InputAction.h"

EInputValueType AInputAction::GetDesiredValueType() {
    return ActionValueType;
}

TMap<EKey, TArray<AInputTrigger*>> AInputAction::GetTriggerConditions() {
    return InputTriggerConditions;
}

TMap<EKey, TArray<AInputModifier*>> AInputAction::GetInputModifiers() {
    return InputModifiers;
}
