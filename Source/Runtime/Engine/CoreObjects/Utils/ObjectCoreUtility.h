#pragma once
#include "../ObjectManager.h"


template<class T = ABaseObject>
T* NewObject(FClass* Class, ABaseObject* ParentObject = nullptr) {
    T* Object = AObjectManager::Get()->InstanciateNewObject<T>(Class, ParentObject);
    Object->Initialize();
    return Object;
};

template<class T = ABaseObject>
T* DuplicateObject(ABaseObject* Object, ABaseObject* ParentObject = nullptr) {
    //TODO
    return nullptr;
}

class ObjectCoreUtility {
public:
};
