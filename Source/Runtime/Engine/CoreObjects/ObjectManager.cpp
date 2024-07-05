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
    bool SuccessfullyDestroy = ObjectRegistry.Remove(TargetObject);
    delete TargetObject;
    TargetObject = nullptr;
    return SuccessfullyDestroy;
}

void AObjectManager::Clear() {
    delete InternFactory;
    InternFactory = nullptr;

    ObjectRegistry.Clear();
}

