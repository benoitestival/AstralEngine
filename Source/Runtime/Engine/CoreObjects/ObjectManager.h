#pragma once
#include <vector>

#include "../../Utils/TemplateUtils.h"
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
    T* InstanciateNewObject(const FClass* Class, ABaseObject* ParentObject = nullptr) {
        ABaseObject* NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
        ObjectRegistry.Add(NewObject);
        return Cast<T>(NewObject);
    }

    bool DestroyObject(ABaseObject* TargetObject);
    void Clear();
private:

    ABaseObject* RootObject = nullptr;
    TArray<ABaseObject*> ObjectRegistry;
    
};

