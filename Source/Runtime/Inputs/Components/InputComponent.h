#pragma once
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
    
    bool ShouldExecuteAction(EKey Key, EInputState KeyState) const;
    void ExecuteAction(EKey Key, EInputState KeyState);

    AInputManager* GetInputManager();
    
public:

protected:
    std::unordered_map<EKey, TArray<AInputAction*>> RegistredActions;
};
