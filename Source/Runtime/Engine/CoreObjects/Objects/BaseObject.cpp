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
    return Parents.Contains(Class);
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
    //Archive.InsertDataInArchive("Class", GetClass());
    
}

void ABaseObject::Deserialize(FArchive& Archive) {
}
