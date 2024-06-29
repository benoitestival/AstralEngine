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

FClass::FClass(std::string ClassID_, const TArray<FClass*>& Parents) : FField(ClassID_), DirectParents(Parents){
    
}

FClass::~FClass() {
    DirectParents.clear();
}

std::string FClass::GetClassName() const {
    return FieldID;
}

TArray<FClass*> FClass::GetAllParents(bool recursive) {
    TArray<FClass*> Parents = TArray<FClass*>();
    for (auto& Parent : DirectParents) {
        Parents.push_back(Parent);
        if (recursive) {
            TArray<FClass*> TopParents = Parent->GetAllParents(recursive);
            Parents.insert(Parents.end(), TopParents.begin(), TopParents.end());
        }
    }
    return Parents;
}

void FClass::AddParent(FClass* ParentClass) {
    DirectParents.push_back(ParentClass);
}

void FClass::AddParents(const TArray<FClass*>& ParentsClass) {
    for (auto Parent: ParentsClass) {
        AddParent(Parent);
    }
}

FArchive& operator<<(FArchive& Ar, FClass* Class) {

    Ar << EArchiveEntryType::AR_START_SUB_ARCHIVE;
    Ar << EArchiveEntryType::AR_KEY << "ClassName";
    Ar << EArchiveEntryType::AR_VALUE << Class->GetClassName();
    Ar << EArchiveEntryType::AR_END_SUB_ARCHIVE;

    return Ar; 
}

FArchive& operator>>(FArchive& Ar, FClass& Class) {
    return Ar; 
}
