#pragma once
#include "../Asset.h"
#include "../../Engine/CoreObjects/Objects/BaseObject.h"
#include "../../Engine/CoreObjects/Systems/EngineSystem.h"

class AAssetRegistry : public AEngineSystem {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AAssetRegistry, AEngineSystem)
    
    virtual void Init() override;
    virtual void DeInit() override;
    


};
