#include "BaseObject.h"

#include "../Systems/ObjectManager.h"


//////////////////////////////////////////////////////////////////////////
ABaseObject::ABaseObject() {
}

ABaseObject* ABaseObject::GetOuter() {
    return Outer;
}

bool ABaseObject::IsA(const FClass& Class) {
    return GetClass() == Class;
}

void ABaseObject::Destroy() {
    AObjectManager::Get()->DestroyObject(this);
}
