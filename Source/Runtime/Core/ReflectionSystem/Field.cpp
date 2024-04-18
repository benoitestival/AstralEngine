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

FClass::FClass() : FClass("", {}){
}

FClass::FClass(std::string ClassID_, const std::vector<FClass>& Parents) : FField(ClassID_), DirectParents(Parents){
}
