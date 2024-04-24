#include "ApplicationRegistries.h"

#include "../Core/Entities/Entity.h"
#include "../Core/Objects/BaseObject.h"
#include "../Core/Systems/ObjectManager.h"
#include "../Engine/Engine.h"
#include "../Engine/Implementations/SFMLEngine.h"
#include "../Serialization/ParserBase.h"
#include "../Serialization/BinaryParsers/BaseBinaryParser.h"
#include "../Serialization/StringParsers/BaseStringParser.h"
#include "../Serialization/StringParsers/Implementations/JsonParser.h"

std::unordered_map<std::string, FClass*> ApplicationRegistries::ClassRegistry = {};
Factory<ABaseObject>* ApplicationRegistries::CreatorRegistry = nullptr;

void ApplicationRegistries::FillRegistries() {
    CreatorRegistry = new Factory<ABaseObject>();
    
    REGISTER_ASTRAL_CLASS(ABaseObject)

    //Managers
    REGISTER_ASTRAL_NO_FACTORY_CLASS(AObjectManager)

    //Engines
    REGISTER_ASTRAL_CLASS(AEngine)
    REGISTER_ASTRAL_CLASS(ASFMLEngine)

    //Objects
    ///////////////////////
    REGISTER_ASTRAL_NO_FACTORY_CLASS(AParserBase)
    REGISTER_ASTRAL_NO_FACTORY_CLASS(ABaseStringParser)
    REGISTER_ASTRAL_NO_FACTORY_CLASS(ABaseBinaryParser)
    REGISTER_ASTRAL_CLASS(AJsonParser)
    //////////////////////
    
    //Entities
    REGISTER_ASTRAL_CLASS(AEntity)
}

void ApplicationRegistries::ClearRegistries() {
    ClassRegistry.clear();
    CreatorRegistry->Clear();

    delete CreatorRegistry;
    CreatorRegistry = nullptr;
}

bool ApplicationRegistries::IsClassRegister(const std::string& ClassName) {
    return ClassRegistry.contains(ClassName);
}

bool ApplicationRegistries::IsCreatorRegister(const FClass* Class) {
    return CreatorRegistry->IsRegistred(Class);
}

void ApplicationRegistries::RegisterClass(FClass* Class) {
    if (!IsClassRegister(Class->GetClassName())) {
        ClassRegistry.insert(std::make_pair(Class->GetClassName(), Class));
    }
}

void ApplicationRegistries::RegisterCreator(FClass* Class, Creator<ABaseObject>* Creator) {
    if (!IsCreatorRegister(Class)) {
        CreatorRegistry->RegisterNew(Class, Creator);
    }
}

FClass* ApplicationRegistries::GetClass(const std::string& ClassName) {
    return ClassRegistry.at(ClassName);
}

Factory<ABaseObject>* ApplicationRegistries::GetCreatorFactory() {
    return CreatorRegistry;
}