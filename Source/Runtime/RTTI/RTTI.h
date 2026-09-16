#pragma once
#include "../Utils/Macro.h"
#include "Field.h"

class ABaseObject;

class RTTI {
public:
    RTTI() = default;
    virtual ~RTTI() = default;
    virtual FClass* GetClass() = 0;
};

struct FClassAutoRegister{
    explicit FClassAutoRegister(FClass* (*RegisterFunction)()) {
        RegisterFunction();
    }
};

#define RTTI_CLASS\
    virtual public RTTI

#define INTERNAL_GET_PARENT_CLASS(ClassID)\
    ClassID::StaticClass(),

#define CREATE_RTTI_BASE_CLASS_INSTANCE(ClassID)\
    TClassConstructor<ClassID>::ConstructClass(#ClassID)

#define GET_ASTRAL_CLASS(ClassID, ...)\
    [](){\
        TArray<FClass*> Parents = {VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)};\
        return AstralEngineStatics::IsClassRegister(#ClassID) ? AstralEngineStatics::GetClass(#ClassID) : AstralEngineStatics::RegisterClassInternal<ClassID>(CREATE_RTTI_BASE_CLASS_INSTANCE(ClassID), Parents);\
    }()\

//Final Macro
#define DECLARE_RTTI(ClassID, ...)\
    [[nodiscard]] virtual FClass* GetClass() override {\
        return ClassID::StaticClass();\
    };\
    [[nodiscard]] static FClass* StaticClass() {\
        static FClass* Class = GET_ASTRAL_CLASS(ClassID, __VA_ARGS__);/*Only one call*/\
        return Class;\
    };\
    inline static const FClassAutoRegister AutoReg_##ClassID{ &ClassID::StaticClass };\

#define DECLARE_SUPER(MainParent)\
    using Super = MainParent;

