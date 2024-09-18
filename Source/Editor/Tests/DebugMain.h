#pragma once
#include "../../Runtime/Engine/CoreObjects/Objects/BaseObject.h"

class ADebugMain : public  ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(ADebugMain, ABaseObject)
    
    int DebugMain();
};
