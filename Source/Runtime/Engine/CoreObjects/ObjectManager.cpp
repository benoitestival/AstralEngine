#include "ObjectManager.h"

#include "../../Render/RenderAPIs/Renderer.h"
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
    bool SuccessfullyDestroy = ObjectsRegistry.Remove(TargetObject);
    delete TargetObject;
    TargetObject = nullptr;
    return SuccessfullyDestroy;
}

void AObjectManager::ClearLivingObjects() {
    for (int INDEX = ObjectsRegistry.Lenght() -1; INDEX >= 0; INDEX--) {
        delete ObjectsRegistry[INDEX];
        ObjectsRegistry[INDEX] = nullptr;
    }
    ObjectsRegistry.Clear();
}

void AObjectManager::ClearManagers() {
    for (int INDEX = SystemsRegistry.Lenght() -1; INDEX >= 0; INDEX--) {
        delete SystemsRegistry[INDEX];
        SystemsRegistry[INDEX] = nullptr;
    }
    SystemsRegistry.Clear();
}

void AObjectManager::Clear() {
    delete InternFactory;
    InternFactory = nullptr;

    ObjectsRegistry.Clear();
}

bool AObjectManager::IsSystemClass(FClass* Class) const{
    return Class->GetAllParents().Contains(AEngineSystem::StaticClass());
}

bool AObjectManager::IsEngineSubClass(FClass* Class) const{
    return Class->GetAllParents().Contains(AEngine::StaticClass());
}

bool AObjectManager::IsSystemAlreadyInstancied(FClass* Class) {
    bool IsSystemInstancied = false;
    for (auto System : SystemsRegistry) {
        if (System->GetClass() == Class) {
            IsSystemInstancied = true;
        }
    }
    return IsSystemInstancied;
}

