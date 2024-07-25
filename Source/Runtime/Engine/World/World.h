#pragma once
#include "../CoreObjects/Objects/BaseObject.h"

class AWorld : public ABaseObject{
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AWorld, ABaseObject)
    
    void Tick(float DeltaTime);
};
