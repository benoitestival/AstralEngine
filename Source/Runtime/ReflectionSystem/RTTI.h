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

#define DECLARE_RTTI(ClassID, ...)\
    [[nodiscard]] virtual FClass* GetClass() override {\
        return ClassID::StaticClass();\
    };\
    [[nodiscard]] static FClass* StaticClass() {\
        FClass* Class = nullptr;\
        if(ApplicationRegistries::IsClassRegister(#ClassID)){\
            Class = ApplicationRegistries::GetClass(#ClassID);\
        }\
        else{\
            /*Should only be called if the App is initialized, TODO Add a check*/\
            Class = new FClass(#ClassID, {VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)});\
        }\
        return Class;\
    };

#define DECLARE_SUPER(MainParent)\
    using Super = MainParent;












