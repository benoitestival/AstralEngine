#pragma once
#include "../../../CoreObjects/Objects/BaseObject.h"
#include "../../Utils/InputUtils.h"

class AInputModifier : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AInputModifier, ABaseObject)

    virtual FInputValue ModifyValue(FInputValue& Value){return Value;};
};
