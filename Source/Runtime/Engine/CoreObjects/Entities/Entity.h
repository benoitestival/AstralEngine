#pragma once
#include "../Objects/BaseObject.h"

class AInputComponent;
/**
 * Base Class for all game entities
 */
class AEntity : public ABaseObject {
public:

    AEntity();
    DECLARE_ASTRAL_ENGINE_CLASS(AEntity, ABaseObject)

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);

public:
    
    AInputComponent* EntityInputComponent;
};

