#pragma once
#include "../Objects/BaseObject.h"

class AEntity;

class AComponent : public ABaseObject{
public:
    AComponent();
    DECLARE_ASTRAL_ENGINE_CLASS(AComponent, ABaseObject)

    virtual void Init(AEntity* Owner);
    virtual void Tick(float DeltaTime);
protected:
    AEntity* ParentEntity;
};
