#pragma once
#include "../../CoreObjects/Objects/BaseObject.h"
#include "../../Maths/Maths.h"
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

    std::unordered_map<EKey, TArray<AInputTrigger*>> GetTriggerConditions();
    std::unordered_map<EKey, TArray<AInputModifier*>> GetInputModifiers();
    
private:
    std::unordered_map<EKey, TArray<AInputTrigger*>> InputTriggerConditions;
    std::unordered_map<EKey, TArray<AInputModifier*>> InputModifiers;
    
    EInputValueType ActionValueType;
};
