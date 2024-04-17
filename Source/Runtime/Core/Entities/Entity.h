#pragma once
#include "../BaseObject.h"

/**
 * Base Class for all game entities
 */
class UEntity : public UBaseObject{
public:
    DECLARE_RTTI(Entity)

    UEntity();
    DECLARE_FACTORY_CONSTRUCTOR(UEntity)

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
};
