// ReSharper disable CppInitializedValueIsAlwaysRewritten
#include "BaseObject.h"
#include "../Systems/ObjectManager.h"


//////////////////////////////////////////////////////////////////////////
ABaseObject::ABaseObject() {
}

FClass* ABaseObject::GetClass() {
    return ABaseObject::StaticClass();
}

FClass* ABaseObject::StaticClass() {
    FClass* Class = nullptr;
    if(RTTIRegistry::IsRegistred("ABaseObject")) {
        Class = RTTIRegistry::GetClass("ABaseObject");
    }
    else {
        Class = new FClass("ABaseObject", {});
        RTTIRegistry::RegisterClass(Class);
    }
    return Class;
}

ABaseObject* ABaseObject::GetOuter() {
    return Outer;
}

bool ABaseObject::IsA(const FClass* Class) {
    return GetClass() == Class;
}

bool ABaseObject::IsChildOf(const FClass* Class) {
    std::vector<FClass*> Parents = GetClass()->GetAllParents();
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
