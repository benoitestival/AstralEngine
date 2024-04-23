#pragma once
#include <unordered_map>
#include "Field.h"
#include "../Utils/Macro.h"

class ABaseObject;

class RTTI {
public:
    RTTI() = default;
    virtual ~RTTI() = default;
    virtual FClass* GetClass() = 0;
};

class RTTIRegistry {
public:
    static bool IsRegistred(const std::string& ClassName);
    static void RegisterClass(FClass* Class);
    static FClass* GetClass(const std::string& ClassName);

    static void Clear();
private:
    static std::unordered_map<std::string, FClass*> ClassRegistry; 
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
        if(RTTIRegistry::IsRegistred(#ClassID)){\
            Class = RTTIRegistry::GetClass(#ClassID);\
        }\
        else{\
            Class = new FClass(#ClassID, {VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)});\
            RTTIRegistry::RegisterClass(Class);\
        }\
        return Class;\
    };

#define DECLARE_RTTI_NO_MULTI_HERIATGE(ClassID, Parent)\
    [[nodiscard]] virtual FClass GetClass() override {return FClass(#ClassID, {Parent::StaticClass()});};\
    [[nodiscard]] static FClass StaticClass() {return FClass(#ClassID, {Parent::StaticClass()});};


#define DECLARE_SUPER(MainParent)\
    using Super = MainParent;












