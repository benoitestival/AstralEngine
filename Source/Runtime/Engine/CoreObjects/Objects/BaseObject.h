// ReSharper disable CppInitializedValueIsAlwaysRewritten
#pragma once
#include <string>

#include "../../../Configs/AstralEngineStatics.h"
#include "../../../Utils/TemplateUtils.h"
#include "../../../Utils/Delegate.h"
#include "../../../Utils/Array.h"
#include "../../../RTTI/RTTI.h"

enum ObjectFlags {
    F_NoFlags = 0x00000000,

    F_Serializable = 0x00000001,
};

#define DECLARE_ASTRAL_ENGINE_CLASS_NO_PARENTS(CLASS)\
    DECLARE_RTTI(CLASS)\


#define DECLARE_ASTRAL_ENGINE_CLASS(CLASS, ...)\
    DECLARE_RTTI(CLASS)\
    DECLARE_SUPER(__VA_ARGS__)\


/**
 * Base class for all game anb memory managed objects
 */

class ABaseObject : RTTI_CLASS {
public:
    ABaseObject();
    DECLARE_ASTRAL_ENGINE_CLASS_NO_PARENTS(ABaseObject)

    [[nodiscard]] ABaseObject* GetOuter();
    [[nodiscard]] bool IsA(const FClass* Class);
    [[nodiscard]] bool IsChildOf(const FClass* Class);

    virtual void Initialize(){};
    void Destroy();

    //Can only work once, you cannot override an outer already set
    void SetOuter(ABaseObject* ObjectOuter);

    virtual void Serialize(FArchive& Archive){};
    virtual void Deserialize(FArchive& Archive){};
protected:
    ABaseObject* Outer = nullptr;
};
