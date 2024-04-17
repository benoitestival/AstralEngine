#pragma once
#include <vector>

#include "../BaseObject.h"

class UObjectManager : public UBaseObject {
public:
    DECLARE_RTTI(UObjectManager)

private:
    UObjectManager();
    static UObjectManager* ObjectManager;
public:

    ~UObjectManager() override;
    static UObjectManager* Get();
    
    template<class T = UBaseObject>
    [[nodiscard]] T* InstanciateNewObject(UBaseObject* ParentObject) {
        T* NewObject = new T(ParentObject == nullptr ? RootObject : ParentObject);
        ObjectRegistry.push_back(NewObject);
        return NewObject;
    }

    bool DestroyObject(UBaseObject* TargetObject);

    void Clear();
private:

    UBaseObject* RootObject = nullptr;
    std::vector<UBaseObject*> ObjectRegistry;
    
};

