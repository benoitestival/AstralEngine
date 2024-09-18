#pragma once
#include "../../../Maths/Maths.h"
#include "../../CoreObjects/Managers/Manager.h"
#include "../../CoreObjects/Objects/BaseObject.h"
#include "../Utils/InputUtils.h"

class AInputComponent;
class AInputAction;



class AInputManager : public AManager {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInputManager, AManager)

    virtual void Init() override;
    void RegisterInputComponent(AInputComponent* InputComponent);
    
    virtual void HandleInputsEvents();
    
    void HandleKeyInput(EKey Key, EInputState InputState);
    virtual bool IsKeyPressed(EKey Key) const;

    EInputState GetPreviousInputState(EKey Key);
    
    FVector2D GetCursorPosition() const;
protected:
    FVector2D CursorPosition;
    
    TMap<EKey, TArray<AInputComponent*>> RegistredComponents;
    TMap<EKey, EInputState> PreviousInputState;
    
};
