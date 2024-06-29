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

struct FClass : public FField{
public:
    FClass();
    FClass(std::string ClassID_, const TArray<FClass*>& Parents);
    ~FClass();
    std::string GetClassName() const;
    TArray<FClass*> GetAllParents(bool recursive = true);
    void AddParent(FClass* ParentClass);
    void AddParents(const TArray<FClass*>& ParentsClass);

    friend FArchive& operator<<(FArchive& Ar, FClass* Class);
    friend FArchive& operator>>(FArchive& Ar, FClass& Class);
protected:
    TArray<FClass*> DirectParents;
};

template <>
struct std::hash<FClass>{
    std::size_t operator()(const FClass Class) const noexcept {
        return std::hash<std::string>()(Class.GetClassName());
    }
};
