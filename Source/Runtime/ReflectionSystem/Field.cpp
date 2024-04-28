#include "Field.h"

FField::FField() : FField(""){
}

FField::FField(std::string FieldID_) : FieldID(FieldID_) {
}

bool FField::operator==(const FField& Other) const {
    return FieldID == Other.FieldID;
}

bool FField::operator!=(const FField& Other) const {
    return !(*this == Other);
}

//////////////////////////////////////////////////////////////////////////////////

FClass::FClass() : FClass("", {}){
}

FClass::FClass(std::string ClassID_, const std::vector<FClass*>& Parents) : FField(ClassID_), DirectParents(Parents){
    
}

FClass::~FClass() {
    DirectParents.clear();
}

std::string FClass::GetClassName() const {
    return FieldID;
}

std::vector<FClass*> FClass::GetAllParents(bool recursive) {
    std::vector<FClass*> Parents = std::vector<FClass*>();
    for (auto& Parent : DirectParents) {
        Parents.push_back(Parent);
        if (recursive) {
            std::vector<FClass*> TopParents = Parent->GetAllParents(recursive);
            Parents.insert(Parents.end(), TopParents.begin(), TopParents.end());
        }
    }
    return Parents;
}

void FClass::AddParent(FClass* ParentClass) {
    DirectParents.push_back(ParentClass);
}

void FClass::AddParents(const std::vector<FClass*>& ParentsClass) {
    for (auto Parent: ParentsClass) {
        AddParent(Parent);
    }
}
