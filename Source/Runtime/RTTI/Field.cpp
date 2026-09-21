#include "Field.h"

#include "../Utils/EnumUtils.h"

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

FClass::FClass(const std::string& ClassID_, const TArray<FClass*>& Parents) : FField(ClassID_), ClassFlags(0) ,DirectParents(Parents){
    ConstructDefaultClassFlags();
}

FClass::~FClass() {
    DirectParents.Clear();
}

std::string FClass::GetClassName() const {
    return FieldID;
}

TArray<FClass*> FClass::GetAllParents(bool recursive) {
    TArray<FClass*> Parents = TArray<FClass*>();
    for (auto& Parent : DirectParents) {
        Parents.Add(Parent);
        if (recursive) {
            Parents.Append(Parent->GetAllParents(recursive));
        }
    }
    return Parents;
}

void FClass::AddParent(FClass* ParentClass) {
    DirectParents.Add(ParentClass);
}

void FClass::AddParents(const TArray<FClass*>& ParentsClass) {
    for (auto Parent: ParentsClass) {
        AddParent(Parent);
    }
}

bool FClass::IsFactoryEligible() const {
    return EnumUtils::DoesntHasFlag(EClassFlags::ECF_Abstact, ClassFlags) && EnumUtils::DoesntHasFlag(EClassFlags::ECF_CPP_Singleton, ClassFlags);
}


void FClass::AddFlag(EClassFlags Flag) {
    EnumUtils::AddFlag(Flag, ClassFlags);
}

void FClass::RemoveFlag(EClassFlags Flag) {
    EnumUtils::RemoveFlag(Flag, ClassFlags);
}

void FClass::ConstructDefaultClassFlags() {
    
}

//
// FArchive& operator<<(FArchive& Ar, FClass* Class) {
//
//     Ar.Option(EArchiveAction::AR_ENTER_SUB_ARCHIVE);
//     Ar.WriteData("ClassName", Class->FieldID);
//     Ar.Option(EArchiveAction::AR_EXIT_SUB_ARCHIVE);
//
//     return Ar; 
// }
//
// FArchive& operator>>(FArchive& Ar, FClass* Class) {
//     
//     Ar.Option(EArchiveAction::AR_ENTER_SUB_ARCHIVE);
//     Ar.ReadData("ClassName", Class->FieldID);
//     Ar.Option(EArchiveAction::AR_EXIT_SUB_ARCHIVE);
//
//     return Ar; 
// }
FArchive& operator<<(FArchive& Ar, TSerializableField<FClass> Class) {
    Ar.InsertDataInArchive("ClassName", Class.GetData()->FieldID);
    return Ar;
}

FArchive& operator>>(FArchive& Ar, TSerializableField<FClass> Class) {
    Ar.ReadDataInArchive("ClassName", Class.GetData()->FieldID);
    return Ar;
}
