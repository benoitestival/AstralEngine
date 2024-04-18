#pragma once
#include <string>
#include <vector>



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
    FClass(std::string ClassID_, const std::vector<FClass>& Parents);

    std::vector<FClass> GetAllParents(bool recursive = true);
protected:
    std::vector<FClass> DirectParents;
};
