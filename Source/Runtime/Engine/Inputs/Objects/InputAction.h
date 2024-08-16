#pragma once
#include "../../CoreObjects/Objects/BaseObject.h"
#include "../Utils/InputUtils.h"


//Object Class holding the callbacks events and all the parameters for their executions

class AInputModifier;
class AInputTrigger;

class AInputAction : public ABaseObject {
public:
    AInputAction() = default;
    DECLARE_ASTRAL_ENGINE_CLASS(AInputAction, ABaseObject)

    EInputValueType GetDesiredValueType();
public:
    
    DECLARE_DELEGATE(FInputActionExecute, FInputValue)
    FInputActionExecute OnInputStart;
    FInputActionExecute OnInputTrigger;
    FInputActionExecute OnInputStop;

    TMap<EKey, TArray<AInputTrigger*>> GetTriggerConditions();
    TMap<EKey, TArray<AInputModifier*>> GetInputModifiers();
    
private:
    TMap<EKey, TArray<AInputTrigger*>> InputTriggerConditions;
    TMap<EKey, TArray<AInputModifier*>> InputModifiers;
    
    EInputValueType ActionValueType;
};
