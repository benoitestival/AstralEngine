#pragma once
#include "../../CoreObjects/Objects/BaseObject.h"
#include "../Utils/InputUtils.h"

class AInputAction;

class AInpuManager : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInpuManager, ABaseObject)

    virtual void Init();

    void HandleKeyboardInput(EKey Key, EKeyboardKeyState ActionType);
    virtual bool IsKeyPressed(EKey Key) const;

    //TODO implement mouse supports
protected:

    std::unordered_map<EKey, TArray<AInputAction*>> RegistredActions;
};
