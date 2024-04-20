#pragma once
#include "Field.h"
#include "../Utils/Macro.h"

class RTTI {
public:
    RTTI() = default;
    virtual ~RTTI() = default;
    virtual FClass GetClass() = 0;
};

#define RTTI_CLASS\
    public RTTI

#define INTERNAL_GET_PARENT_CLASS(ClassID)\
    ClassID::StaticClass()

#define DECLARE_RTTI(ClassID, ...)\
    [[nodiscard]] virtual FClass GetClass() override {return FClass(#ClassID, {VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)});};\
    [[nodiscard]] static FClass StaticClass() {return FClass(#ClassID, {VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)});};
