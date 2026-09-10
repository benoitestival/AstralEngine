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

#define INTERNAL_CHECK_AND_REGISTER(ClassID)\
    if (!AstralEngineStatics::IsClassRegister(#ClassID)){\
        ClassID::StaticClass();\
    }\

#define CREATE_RTTI_BASE_CLASS_INSTANCE(ClassID)\
    new FClass(#ClassID, {})

#define REGISTER_ASTRAL_CLASS(Class)\
    if(!AstralEngineStatics::IsClassRegister(#Class)){\
        FClass* Instance##Class = CREATE_RTTI_BASE_CLASS_INSTANCE(Class);\
        AstralEngineStatics::RegisterClass(Instance##Class);\
        AstralEngineStatics::RegisterCreator(Instance##Class, new DerivedCreator<ABaseObject, Class>());\
    }\

#define LINK_ASTRAL_CLASS_PARENTS(Class, ...)\
    Class::StaticClass()->AddParents({VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)});     

#define DECLARE_RTTI(ClassID, ...)\
    [[nodiscard]] virtual FClass* GetClass() override {\
        return ClassID::StaticClass();\
    };\
    [[nodiscard]] static FClass* StaticClass() {\
        FClass* Class = nullptr;\
        if(AstralEngineStatics::IsClassRegister(#ClassID)){\
            Class = AstralEngineStatics::GetClass(#ClassID);\
        }\
        else{\
            VA_ARGS_CODE_EXECUTE(INTERNAL_CHECK_AND_REGISTER,__VA_ARGS__)\
            REGISTER_ASTRAL_CLASS(ClassID)\
            LINK_ASTRAL_CLASS_PARENTS(ClassID, __VA_ARGS__)\
            Class = AstralEngineStatics::GetClass(#ClassID);\
        }\
        return Class;\
    };

#define DECLARE_SUPER(MainParent)\
    using Super = MainParent;

   











