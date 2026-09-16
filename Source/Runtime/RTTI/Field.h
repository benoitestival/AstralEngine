#pragma once
#include <string>
#include <vector>

#include "../Serialization/Archive/Archive.h"
#include "../Utils/Array.h"


struct FField {
public:
    FField();
    FField(std::string FieldID_);
    
    bool operator==(const FField& Other) const;
    bool operator!=(const FField& Other) const;
protected:
    std::string FieldID;
};

enum EClassFlags {
    ECF_Singleton,
    ECF_Abstact,
};

struct FClass : public FField{
public:
    FClass();
    FClass(const std::string& ClassID_, const TArray<FClass*>& Parents);
    ~FClass();
    std::string GetClassName() const;
    TArray<FClass*> GetAllParents(bool recursive = true);
    void AddParent(FClass* ParentClass);
    void AddParents(const TArray<FClass*>& ParentsClass);
    bool IsFactoryEligible() const;

    //TODO make a real flag system
    void AddFlag(EClassFlags Flag);
    void RemoveFlag(EClassFlags Flag);
    
    friend FArchive& operator<<(FArchive& Ar, TSerializableField<FClass> Class);
    friend FArchive& operator>>(FArchive& Ar, TSerializableField<FClass> Class);
    
protected:
    bool IsClassFactoryEligible;//TODO make it a flag
    TArray<FClass*> DirectParents;
};



template<typename T>
struct TClassFlags {
    static void Apply(FClass* Class) {}// default impl
};   

template<typename T>
struct TClassConstructor {
    static FClass* ConstructClass(const std::string& ClassID_) {
        FClass* Class = new FClass(ClassID_, {});
        TClassFlags<T>::Apply(Class);
        return Class;
    }
};

#define DECLARE_CLASS_FLAGS(ClassID, ...)\
    template<>\
    struct TClassFlags<ClassID> {\
        static void Apply(FClass* Class) {\
            __VA_ARGS__ /*Apply all the code for inserting the flags*/\
        } \
    }\

template <>
struct std::hash<FClass>{
    std::size_t operator()(const FClass Class) const noexcept {
        return std::hash<std::string>()(Class.GetClassName());
    }
};
