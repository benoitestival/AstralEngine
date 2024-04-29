#include "ObjectManager.h"


AObjectManager* AObjectManager::ObjectManager = nullptr;

AObjectManager::AObjectManager() {
    InternFactory = new Factory<ABaseObject>();
    TArray<FClass*> RegistredClasses = AstralEngineStatics::GetAllFactoryClasses();
    for(auto& Class : RegistredClasses) {
        InternFactory->RegisterNew(Class, AstralEngineStatics::GetCreator(Class));
    }
}

AObjectManager::~AObjectManager() {
    Clear();
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
    delete InternFactory;
    InternFactory = nullptr;

    ObjectRegistry.clear();
}

