#pragma once
#include <string>

#include "../Maths/Vector2D.h"
#include "../Utils/Delegate.h"

struct FClass {
    FClass();
    FClass(std::string ClassName);

    bool operator==(const FClass& Other) const;
    bool operator!=(const FClass& Other) const;
private:
    std::string ClassID;
};

class RTTI {
public:
    RTTI() = default;
    virtual ~RTTI() = default;
    virtual FClass GetClass() = 0;
};

#define RTTI_CLASS\
    public RTTI

#define DECLARE_RTTI(ClassID)\
    [[nodiscard]] virtual FClass GetClass() override {return FClass(#ClassID);};\
    [[nodiscard]] static FClass GetStaticClass() {return FClass(#ClassID);};

#define DECLARE_FACTORY_CONSTRUCTOR(ClassName)\
    ClassName(UBaseObject* ObjectOuter){Outer = ObjectOuter;};

/**
 * Base class for all game anb memory managed objects
 */

class UBaseObject : RTTI_CLASS {
public:
    DECLARE_RTTI(UBaseObject)
    
    UBaseObject();
    DECLARE_FACTORY_CONSTRUCTOR(UBaseObject)
    
    [[nodiscard]] UBaseObject* GetOuter();
    [[nodiscard]] bool IsA(const FClass& Class);

    DECLARE_DELEGATE(FOnHit, UBaseObject*)
    FOnHit OnHit;

    void Test(UBaseObject* Object);
    
    void Destroy();
protected:
    UBaseObject* Outer = nullptr;
};
