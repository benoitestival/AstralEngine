#pragma once
#include <unordered_map>

#include "../RTTI/Field.h"


class ABaseObject;

template <class BaseClass = ABaseObject>//Base class for polymorphoc usage
class Creator{
public:
    virtual ~Creator(){}
    virtual BaseClass* Create(ABaseObject* Outer) = 0;
};

template <class BaseClass = ABaseObject, class DerivedClass = ABaseObject>// Real implementation who take a Derived param
class DerivedCreator : public Creator<BaseClass>{
public:
    virtual BaseClass* Create(ABaseObject* Outer) override {
        BaseClass* Object = new DerivedClass();
        Object->SetOuter(Outer);
        return Object;
    }
};

template <class BaseClass = ABaseObject>
class Factory {
public:
    Factory() = default;
    ~Factory() {
        Clear();
    };
    
    void RegisterNew(const FClass* ObjectClass, Creator<BaseClass>* FactoryCreator){
        if (!IsRegistred(ObjectClass)) {
            FactoryConstructors.insert(std::make_pair(ObjectClass->GetClassName(), FactoryCreator));
        }
    };

    bool IsRegistred(const FClass* ObjectClass) {
        return FactoryConstructors.contains(ObjectClass->GetClassName());  
    };
    
    BaseClass* ConstructNew(const FClass* Class, ABaseObject* Outer = nullptr) {
        BaseClass* Object = nullptr;
        if (IsRegistred(Class)) {
            Object = FactoryConstructors.at(Class->GetClassName())->Create(Outer);
        }
        return Object;
    };

    void Clear() {
        FactoryConstructors.clear();
    }
    
public:
    std::unordered_map<std::string, Creator<BaseClass>*> FactoryConstructors;
};
