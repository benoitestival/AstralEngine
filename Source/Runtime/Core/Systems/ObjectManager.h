#pragma once
#include <vector>

#include "../../Utils/Factory.h"
#include "../Objects/BaseObject.h"


class AObjectManager : public ABaseObject {
public:
    DECLARE_ASTRAL_ENGINE_CLASS(AObjectManager, ABaseObject)
    
private:
    AObjectManager();
    static AObjectManager* ObjectManager;
public:
    ~AObjectManager() override;
    static AObjectManager* Get();

    Factory<ABaseObject>* InternFactory;
    template<class T = ABaseObject>
    [[nodiscard]] T* InstanciateNewObject(const FClass& Class, ABaseObject* ParentObject = nullptr) {
        if (!InternFactory->IsRegistred(Class)) {
            InternFactory->RegisterNew(Class, new DerivedCreator<ABaseObject, T>());
        }
        ABaseObject* NewObject = InternFactory->ConstructNew(Class, ParentObject != nullptr ? ParentObject : RootObject);
        ObjectRegistry.push_back(NewObject);
        return (T*)NewObject;
    }

    bool DestroyObject(ABaseObject* TargetObject);

    void Clear();
private:

    ABaseObject* RootObject = nullptr;
    std::vector<ABaseObject*> ObjectRegistry;
    
};

