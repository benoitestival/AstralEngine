#pragma once
#include "../../../Maths/Maths.h"
#include "../../CoreObjects/Systems/EngineSystem.h"
#include "../Utils/InputUtils.h"

class AInputComponent;
class AInputAction;



class AInputManager : public AEngineSystem {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInputManager, AEngineSystem)

    virtual void Init() override;
    void RegisterInputComponent(AInputComponent* InputComponent);
    
    virtual void HandleInputsEvents(float DeltaTime);

public:
    void HandleKeyInput(EKey Key, FInputParams InputState);
    virtual bool IsKeyPressed(EKey Key) const;

    

    EInputState GetPreviousInputState(EKey Key);
    
    virtual FVector2D GetCursorPosition() const;
    virtual void SetCursorPosition(const FVector2D& Pos);

protected:
    
    TMap<EKey, TArray<AInputComponent*>> RegistredComponents;
private:
    TMap<EKey, EInputState> PreviousInputState;
    
};
