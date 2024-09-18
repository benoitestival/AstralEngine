#include "ObjectManager.h"

#include "../../Render/Systems/RenderManager.h"
#include "../Engine/Engine.h"
#include "../Inputs/Systems/InpuManager.h"
#include "../Time/TimerManager.h"


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

void AObjectManager::ClearLivingObjects() {
    for (int INDEX = ObjectRegistry.Lenght() -1; INDEX >= 0; INDEX--) {
        delete ObjectRegistry[INDEX];
        ObjectRegistry[INDEX] = nullptr;
    }
    ObjectRegistry.Clear();
}

void AObjectManager::ClearManagers() {
    for (int INDEX = ManagerRegistry.Lenght() -1; INDEX >= 0; INDEX--) {
        delete ManagerRegistry[INDEX];
        ManagerRegistry[INDEX] = nullptr;
    }
    ManagerRegistry.Clear();
}

void AObjectManager::Clear() {
    delete InternFactory;
    InternFactory = nullptr;

    ObjectRegistry.Clear();
}

bool AObjectManager::IsManagerSubClass(FClass* Class) const{
    return Class->GetAllParents().Contains(AManager::StaticClass());
}

bool AObjectManager::IsEngineSubClass(FClass* Class) const{
    return Class->GetAllParents().Contains(AEngine::StaticClass());
}

