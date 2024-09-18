#pragma once
#include <vector>

#include "../../Utils/TemplateUtils.h"
#include "Managers/Manager.h"
#include "Objects/BaseObject.h"


class AObjectManager : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AObjectManager, ABaseObject)
    
private:
    AObjectManager();
    static AObjectManager* ObjectManager;
public:
    ~AObjectManager() override;
    static AObjectManager* Get();
    
private:
    Factory<ABaseObject>* InternFactory;
public:
    template<class T = ABaseObject>
    T* InstanciateNewObject(FClass* Class, ABaseObject* ParentObject = nullptr) {
        ABaseObject* NewObject = nullptr;
        if (IsEngineSubClass(Class)) {
            if (Engine == nullptr) {
                NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
                Engine = NewObject;
            }
        }
        else if (IsManagerSubClass(Class)) {
            bool CanCreateManager = true;
            for (auto Manager : ManagerRegistry) {
                if (Manager->GetClass() == Class) {
                    CanCreateManager = false;
                }
            }
            if (CanCreateManager) {
                NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
                ManagerRegistry.Add(NewObject);
            }
        }
        else {
            NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
            ObjectRegistry.Add(NewObject);
        }
        return Cast<T>(NewObject);
    }

    bool DestroyObject(ABaseObject* TargetObject);
    void ClearLivingObjects();
    void ClearManagers();
    void Clear();
private:
    bool IsManagerSubClass(FClass* Class) const;
    bool IsEngineSubClass(FClass* Class) const;
private:
    ABaseObject* RootObject = nullptr;
    TArray<ABaseObject*> ObjectRegistry;
    TArray<ABaseObject*> ManagerRegistry;
    ABaseObject* Engine = nullptr;
    
};

