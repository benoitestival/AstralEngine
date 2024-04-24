#include "ObjectManager.h"

#include "../../Maths/Maths.h"

AObjectManager* AObjectManager::ObjectManager = nullptr;

AObjectManager::AObjectManager() {
}

AObjectManager::~AObjectManager() {
}

AObjectManager* AObjectManager::Get() {
    if (ObjectManager == nullptr) {
        ObjectManager = new AObjectManager();
    }
    return ObjectManager;
}

bool AObjectManager::DestroyObject(ABaseObject* TargetObject) {
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

