#pragma once
#include "../Objects/BaseObject.h"

/**
 * Base Class for all game entities
 */
class AEntity : public ABaseObject {
public:
    DECLARE_RTTI(AEntity, ABaseObject)

    AEntity();
    DECLARE_FACTORY_CONSTRUCTOR(AEntity)

    virtual void BeginPlay();
    virtual void Tick(float DeltaTime);
};

class ATest : public AEntity {
public:
    DECLARE_RTTI(ATest, AEntity)

    ATest(){};
   // DECLARE_FACTORY_CONSTRUCTOR(AEntity)
};
