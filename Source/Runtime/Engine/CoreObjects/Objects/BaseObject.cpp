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

void ABaseObject::SerializeEditor(FStringArchive& Archive) {
    
}

void ABaseObject::DeserializeEditor(FStringArchive& Archive) {
    
}

void ABaseObject::SerializeRuntime(FBinaryArchive& Archive) {
}

void ABaseObject::DeserializeRuntime(FBinaryArchive& Archive) {
}
