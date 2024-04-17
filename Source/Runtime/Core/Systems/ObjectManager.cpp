#include "ObjectManager.h"

UObjectManager* UObjectManager::ObjectManager = nullptr;

UObjectManager::UObjectManager() {
}

UObjectManager::~UObjectManager() {
    Clear();
}

UObjectManager* UObjectManager::Get() {
    if (ObjectManager == nullptr) {
        ObjectManager = new UObjectManager();
    }
    return ObjectManager;
}

bool UObjectManager::DestroyObject(UBaseObject* TargetObject) {
    bool SuccessfullyDestroy = false;

    auto Iterator = std::find(ObjectRegistry.begin(), ObjectRegistry.end(), TargetObject);
    if (Iterator != ObjectRegistry.end()) {
        ObjectRegistry.erase(Iterator);
        delete TargetObject;
        TargetObject = nullptr;

        SuccessfullyDestroy = true;
    }
    
    return SuccessfullyDestroy;
}

void UObjectManager::Clear() {
    ObjectRegistry.clear();
}
