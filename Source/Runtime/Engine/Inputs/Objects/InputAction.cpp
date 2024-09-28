#include "InputAction.h"

EInputValueType AInputAction::GetDesiredValueType() {
    return ActionValueType;
}

void AInputAction::SetDesiredValueType(EInputValueType Type) {
    ActionValueType = Type;
}

TMap<EKey, TArray<AInputTrigger*>> AInputAction::GetTriggerConditions() {
    return InputTriggerConditions;
}

TMap<EKey, TArray<AInputModifier*>> AInputAction::GetInputModifiers() {
    return InputModifiers;
}
