#include "RTTI.h"

//Factory<ABaseObject>* RTTIRegistry::CreatorRegistry = nullptr;//TODO handle instanciate
std::unordered_map<std::string, FClass*> RTTIRegistry::ClassRegistry = {};

bool RTTIRegistry::IsRegistred(const std::string& ClassName) {
    return ClassRegistry.contains(ClassName);
}

void RTTIRegistry::RegisterClass(FClass* Class) {
    if (!IsRegistred(Class->GetClassName())) {
        ClassRegistry.insert(std::make_pair(Class->GetClassName(), Class));
    }
}

FClass* RTTIRegistry::GetClass(const std::string& ClassName) {
    return ClassRegistry.at(ClassName);
}

void RTTIRegistry::Clear() {
    ClassRegistry.clear();
    //CreatorRegistry->Clear();
}
