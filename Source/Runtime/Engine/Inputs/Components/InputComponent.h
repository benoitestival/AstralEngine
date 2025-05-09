﻿#pragma once
#include "../../CoreObjects/Components/Component.h"
#include "../Utils/InputUtils.h"


class AInputManager;
class AInputAction;

class AInputComponent : public AComponent{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInputComponent, AComponent)

    void RegisterAction(EKey Key, AInputAction* Action);
    void UnRegisterActionFromAllKeys(AInputAction* Action);
    void UnRegisterActionForKey(AInputAction* Action, EKey Key);
    
    bool ShouldExecuteAction(EKey Key, FInputParams InputParams) const;
    void ExecuteAction(EKey Key, FInputParams InputParams);

    TArray<EKey> GetAllMappedKeys();
private:
    AInputManager* GetInputManager();
public:

protected:
    TMap<EKey, TArray<AInputAction*>> RegistredActions;
};
