#pragma once
#include <unordered_map>

#include "../Utils/Macro.h"
#include "Field.h"

class ABaseObject;

class RTTI {
public:
    RTTI() = default;
    virtual ~RTTI() = default;
    virtual FClass* GetClass() = 0;
};

#define RTTI_CLASS\
    public RTTI

#define INTERNAL_GET_PARENT_CLASS(ClassID)\
    ClassID::StaticClass()

#define CREATE_RTTI_BASE_CLASS_INSTANCE(ClassID)\
    new FClass(#ClassID, {})

#define CREATE_RTTI_CLASS_INSTANCE(ClassID, ...)\
    new FClass(#ClassID, {VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)})

#define DECLARE_RTTI(ClassID)\
    [[nodiscard]] virtual FClass* GetClass() override {\
        return ClassID::StaticClass();\
    };\
    [[nodiscard]] static FClass* StaticClass() {\
        FClass* Class = nullptr;\
        if(AstralEngineStatics::IsClassRegister(#ClassID)){\
            Class = AstralEngineStatics::GetClass(#ClassID);\
        }\
        return Class;\
    };

#define DECLARE_SUPER(MainParent)\
    using Super = MainParent;












