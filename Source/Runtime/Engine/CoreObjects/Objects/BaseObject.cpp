// ReSharper disable CppInitializedValueIsAlwaysRewritten
#include "BaseObject.h"

#include "../ObjectManager.h"


//////////////////////////////////////////////////////////////////////////
ABaseObject::ABaseObject() {
}

ABaseObject* ABaseObject::GetOuter() {
    return Outer;
}

bool ABaseObject::IsA(const FClass* Class) {
    return GetClass() == Class;
}

bool ABaseObject::IsChildOf(const FClass* Class) {
    TArray<FClass*> Parents = GetClass()->GetAllParents();
    return std::find(Parents.begin(), Parents.end(), Class) != Parents.end();
}

void ABaseObject::Destroy() {
    AObjectManager::Get()->DestroyObject(this);
}

void ABaseObject::SetOuter(ABaseObject* ObjectOuter) {
    if (Outer == nullptr) {
        Outer = ObjectOuter;
    }
}

void ABaseObject::Serialize(FArchive& Archive) {
    Archive.Option(EArchiveAction::AR_ENTER_SUB_ARCHIVE);
    
    Archive.WriteData("Class", GetClass());
    
    Archive.Option(EArchiveAction::AR_EXIT_SUB_ARCHIVE);
}

void ABaseObject::Deserialize(FArchive& Archive) {
    
}
