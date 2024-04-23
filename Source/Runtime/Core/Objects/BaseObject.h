// ReSharper disable CppInitializedValueIsAlwaysRewritten
#pragma once
#include <string>
#include "../../ReflectionSystem/RTTI.h"
#include "../../Utils/Delegate.h"
#include "../../Utils/Factory.h"
#include "../../Utils/Macro.h"


#define DECLARE_ASTRAL_ENGINE_CLASS(CLASS, ...)\
    DECLARE_RTTI(CLASS, __VA_ARGS__)\
    DECLARE_SUPER(__VA_ARGS__)\


/**
 * Base class for all game anb memory managed objects
 */

class ABaseObject : RTTI_CLASS {
public:
    ABaseObject();

    [[nodiscard]] virtual FClass* GetClass() override;
    [[nodiscard]] static FClass* StaticClass();

    [[nodiscard]] ABaseObject* GetOuter();
    [[nodiscard]] bool IsA(const FClass* Class);
    [[nodiscard]] bool IsChildOf(const FClass* Class);
    
    void Destroy();

    //Can only work once, you cannot override an outer already set
    void SetOuter(ABaseObject* ObjectOuter);
protected:
    ABaseObject* Outer = nullptr;
};
