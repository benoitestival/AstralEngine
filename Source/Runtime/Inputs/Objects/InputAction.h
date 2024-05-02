#pragma once
#include "../../CoreObjects/Objects/BaseObject.h"
#include "../Utils/InputUtils.h"


class AInputAction : public ABaseObject {
public:
    AInputAction() = default;
    DECLARE_ASTRAL_ENGINE_CLASS(AInputAction, ABaseObject)

    bool ShouldExecuteKeyboardAction(EKey Key, EKeyboardKeyState KeyState) const;
    void ExecuteKeyboardAction(EKey Key, EKeyboardKeyState KeyState);

    //TODO implement mouse supports
    
public:
    DECLARE_DELEGATE(FInputActionExecute, EKey, AInputAction*)
    FInputActionExecute OnInputStart;
    FInputActionExecute OnInputTrigger;
    FInputActionExecute OnInputStop;
private:
    //TODO Redo this part in a more modular way to handle mouse and joystick properly 
    EKey LinkedKey;
    EKeyboardKeyState LinkedKeyState;
};
