#pragma once
#include "../Objects/BaseObject.h"


class AEngineSystem : public ABaseObject {
public:
    AEngineSystem() = default;
    DECLARE_ASTRAL_ENGINE_CLASS(AEngineSystem, ABaseObject)

    virtual void Init();
    virtual void DeInit();
};

DECLARE_CLASS_FLAGS(AEngineSystem,
    Class->AddFlag(EClassFlags::ECF_Abstact);
);

