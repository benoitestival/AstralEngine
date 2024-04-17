#include "BaseObject.h"

#include "Systems/ObjectManager.h"

FClass::FClass() : FClass(""){
}

FClass::FClass(std::string ClassName) : ClassID(ClassName) {
    
}

bool FClass::operator==(const FClass& Other) const {
    return ClassID == Other.ClassID;
}

bool FClass::operator!=(const FClass& Other) const {
    return !(*this == Other);
}


//////////////////////////////////////////////////////////////////////////

UBaseObject::UBaseObject() {
}

UBaseObject* UBaseObject::GetOuter() {
    return Outer;
}

bool UBaseObject::IsA(const FClass& Class) {
    return GetClass() == Class;
}

void UBaseObject::Test(UBaseObject* Object) {
    
}

void UBaseObject::Destroy() {
    UObjectManager::Get()->DestroyObject(this);
}
