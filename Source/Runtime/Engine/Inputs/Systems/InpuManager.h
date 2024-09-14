#pragma once
#include "../../CoreObjects/Objects/BaseObject.h"
#include "../Utils/InputUtils.h"

class AInputComponent;
class AInputAction;



class AInputManager : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInputManager, ABaseObject)

    virtual void Init();

    virtual void HandleInputsEvents();
    
    void HandleKeyInput(EKey Key, EInputState InputState);
    virtual bool IsKeyPressed(EKey Key) const;

    EInputState GetPreviousInputState(EKey Key);
protected:

    TMap<EKey, TArray<AInputComponent*>> RegistredComponents;
    TMap<EKey, EInputState> PreviousInputState;
};
