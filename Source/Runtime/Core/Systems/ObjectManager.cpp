#include "ObjectManager.h"

#include "../../Maths/Maths.h"

AObjectManager* AObjectManager::ObjectManager = nullptr;

AObjectManager::AObjectManager() {
    InternFactory = new Factory<ABaseObject>();
}

AObjectManager::~AObjectManager() {
    Clear();

    FVector2D A;
    FVector2D B;
    A + B;
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

void AObjectManager::Clear() {
    ObjectRegistry.clear();
    delete InternFactory;
}
