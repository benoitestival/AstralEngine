#pragma once
#include <functional>
#include <map>
#include "../ReflectionSystem/Field.h"

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
    
    void RegisterNew(const FClass& ObjectClass, Creator<BaseClass>* FactoryCreator){
        if (!FactoryConstructors.contains(ObjectClass)) {
            FactoryConstructors.insert(std::make_pair(ObjectClass, FactoryCreator));
        }
    };

    bool IsRegistred(const FClass& ObjectClass) {
        return FactoryConstructors.contains(ObjectClass);  
    };
    
    BaseClass* ConstructNew(const FClass& Class, ABaseObject* Outer = nullptr) {
        BaseClass* Object = nullptr;
        if (FactoryConstructors.contains(Class)) {
            Object = FactoryConstructors.at(Class)->Create(Outer);
        }
        return Object;
    };

    void Clear() {
        FactoryConstructors.clear();
    }
    
public:
    std::unordered_map<FClass, Creator<BaseClass>*> FactoryConstructors;
};
