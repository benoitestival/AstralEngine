#include "InputAction.h"

EInputValueType AInputAction::GetDesiredValueType() {
    return ActionValueType;
}

std::unordered_map<EKey, TArray<AInputTrigger*>> AInputAction::GetTriggerConditions() {
    return InputTriggerConditions;
}

std::unordered_map<EKey, TArray<AInputModifier*>> AInputAction::GetInputModifiers() {
    return InputModifiers;
}
