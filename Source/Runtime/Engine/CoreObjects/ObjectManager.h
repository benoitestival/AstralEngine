#pragma once
#include <vector>

#include "../../Utils/Factory.h"
#include "../../Utils/TemplateUtils.h"

class ABaseObject;

class AObjectManager {
public:

private:
    AObjectManager();
    static AObjectManager* ObjectManager;
public:
    ~AObjectManager();
    static AObjectManager* Get();
    
private:
    Factory<ABaseObject>* InternFactory;
public:
    template<class T = ABaseObject>
    T* InstanciateNewObject(FClass* Class, ABaseObject* ParentObject = nullptr) {
        ABaseObject* NewObject = nullptr;
        if (IsEngineSubClass(Class)) {
            if (Engine == nullptr) {
                Engine = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
                NewObject = Engine;
            }
        }
        else if (IsSystemClass(Class)) {
            if (!IsSystemAlreadyInstancied(Class)) {
                NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
                SystemsRegistry.Add(NewObject);
            }
        }
        else {
            NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
            ObjectsRegistry.Add(NewObject);
        }
        return Cast<T>(NewObject);
    }

    bool DestroyObject(ABaseObject* TargetObject);
    void ClearLivingObjects();
    void ClearManagers();
    void Clear();
private:
    bool IsSystemClass(FClass* Class) const;
    bool IsEngineSubClass(FClass* Class) const;

    bool IsSystemAlreadyInstancied(FClass* Class);
private:
    ABaseObject* RootObject = nullptr;
    TArray<ABaseObject*> ObjectsRegistry;
    TArray<ABaseObject*> SystemsRegistry;
    ABaseObject* Engine = nullptr;
    
};

