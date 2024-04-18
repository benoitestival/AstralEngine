#pragma once
#include <vector>

#include "../Objects/BaseObject.h"


class AObjectManager : public ABaseObject {
public:
    DECLARE_RTTI(UObjectManager, ABaseObject)

private:
    AObjectManager();
    static AObjectManager* ObjectManager;
public:

    ~AObjectManager() override;
    static AObjectManager* Get();
    
    template<class T = ABaseObject>
    [[nodiscard]] T* InstanciateNewObject(ABaseObject* ParentObject) {
        T* NewObject = new T(ParentObject == nullptr ? RootObject : ParentObject);
        ObjectRegistry.push_back(NewObject);
        return NewObject;
    }

    bool DestroyObject(ABaseObject* TargetObject);

    void Clear();
private:

    ABaseObject* RootObject = nullptr;
    std::vector<ABaseObject*> ObjectRegistry;
    
};

