#pragma once
#include <string>

#include "../ReflectionSystem/RTTI.h"


#define DECLARE_FACTORY_CONSTRUCTOR(ClassName)\
    ClassName(ABaseObject* ObjectOuter){Outer = ObjectOuter;};

/**
 * Base class for all game anb memory managed objects
 */

class ABaseObject : RTTI_CLASS {
public:

    DECLARE_RTTI(ABaseObject)
    
    ABaseObject();
    DECLARE_FACTORY_CONSTRUCTOR(ABaseObject)
    
    [[nodiscard]] ABaseObject* GetOuter();
    [[nodiscard]] bool IsA(const FClass& Class);
    [[nodiscard]] bool IsChildOf(const FClass& Class);
    
    void Destroy();
protected:
    ABaseObject* Outer = nullptr;
};
