#pragma once
#include "../Engine/CoreObjects/Objects/BaseObject.h"

class AWindow : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AWindow, ABaseObject)

    virtual void Construct();
    virtual void Tick(float DeltaTime);
    virtual void Destroy();

    
    virtual bool IsOpen() const;
};
