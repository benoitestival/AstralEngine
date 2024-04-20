#pragma once
#include <string>

#include "../../ReflectionSystem/RTTI.h"


#define DECLARE_ASTRAL_ENGINE_CLASS(CLASS, ...)\
    DECLARE_RTTI(CLASS, __VA_ARGS__)\


/**
 * Base class for all game anb memory managed objects
 */

class ABaseObject : RTTI_CLASS {
public:
    ABaseObject();
    
    //DECLARE_ASTRAL_ENGINE_CLASS(ABaseObject)
    //todo investigate why it doesnt work with a macro
    [[nodiscard]] virtual FClass GetClass() override {return FClass("ABaseObject", {});};
    [[nodiscard]] static FClass StaticClass() {return FClass("ABaseObject", {});};

    
    [[nodiscard]] ABaseObject* GetOuter();
    [[nodiscard]] bool IsA(const FClass& Class);
    [[nodiscard]] bool IsChildOf(const FClass& Class);
    
    void Destroy();
    void SetOuter(ABaseObject* ObjectOuter);
protected:
    ABaseObject* Outer = nullptr;
};
