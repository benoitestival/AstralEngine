﻿// ReSharper disable CppInitializedValueIsAlwaysRewritten
#include "BaseObject.h"

#include "../ObjectManager.h"
#include "../../Utils/Array.h"


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
