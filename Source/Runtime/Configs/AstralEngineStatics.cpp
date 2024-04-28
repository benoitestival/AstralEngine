#include "AstralEngineStatics.h"

#include "../Core/Entities/Entity.h"
#include "../Core/Objects/BaseObject.h"
#include "../Core/Systems/ObjectManager.h"
#include "../Core/Systems/Inputs/InpuManager.h"
#include "../Core/Systems/Inputs/Implementations/SFMLInputManager.h"
#include "../Engine/Engine.h"
#include "../Engine/Implementations/SFMLEngine.h"
#include "../Serialization/ParserBase.h"
#include "../Serialization/BinaryParsers/BaseBinaryParser.h"
#include "../Serialization/StringParsers/BaseStringParser.h"
#include "../Serialization/StringParsers/Implementations/JsonParser.h"

Application* AstralEngineStatics::AstralEngineApp = nullptr;
std::unordered_map<std::string, FClass*> AstralEngineStatics::ClassRegistry = {};
std::unordered_map<std::string, Creator<ABaseObject>*> AstralEngineStatics::CreatorRegistry = {};

void AstralEngineStatics::InitAstralEngineStatics(Application* App) {
    AstralEngineApp = App;
    RegisterAstralClasses();
    LinkAstralClassesParents();
}

void AstralEngineStatics::ClearAstralEngineStatics() {
    ClassRegistry.clear();
    CreatorRegistry.clear();
}

void AstralEngineStatics::RegisterAstralClasses() {
    REGISTER_ASTRAL_CLASS(ABaseObject)

    //Managers
    REGISTER_ASTRAL_SINGLETON_CLASS(AObjectManager)
    REGISTER_ASTRAL_CLASS(AInpuManager)
    REGISTER_ASTRAL_CLASS(ASFMLInputManager)

    //Engines
    REGISTER_ASTRAL_CLASS(AEngine)
    REGISTER_ASTRAL_CLASS(ASFMLEngine)

    //Objects
    ///////////////////////
    REGISTER_ASTRAL_PURE_CLASS(AParserBase)
    REGISTER_ASTRAL_PURE_CLASS(ABaseStringParser)
    REGISTER_ASTRAL_PURE_CLASS(ABaseBinaryParser)
    REGISTER_ASTRAL_CLASS(AJsonParser)
    //////////////////////
    
    //Entities
    REGISTER_ASTRAL_CLASS(AEntity)
}

void AstralEngineStatics::LinkAstralClassesParents() {
    //Managers
    LINK_ASTRAL_CLASS_PARENTS(AObjectManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AInpuManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLInputManager, AInpuManager)
    
    //Engines
    LINK_ASTRAL_CLASS_PARENTS(AEngine, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLEngine, AEngine)
    
    //Objects
    ///////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AParserBase, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ABaseStringParser, AParserBase)
    LINK_ASTRAL_CLASS_PARENTS(ABaseBinaryParser, AParserBase)
    LINK_ASTRAL_CLASS_PARENTS(AJsonParser, ABaseStringParser)

    //Entities
    LINK_ASTRAL_CLASS_PARENTS(AEntity, ABaseObject)
}

bool AstralEngineStatics::IsClassRegister(const std::string& ClassName) {
    return ClassRegistry.contains(ClassName);
}

bool AstralEngineStatics::IsCreatorRegister(const FClass* Class) {
    return CreatorRegistry.contains(Class->GetClassName());
}

void AstralEngineStatics::RegisterClass(FClass* Class) {
    if (!IsClassRegister(Class->GetClassName())) {
        ClassRegistry.insert(std::make_pair(Class->GetClassName(), Class));
    }
}

void AstralEngineStatics::RegisterCreator(FClass* Class, Creator<ABaseObject>* Creator) {
    if (!IsCreatorRegister(Class)) {
        CreatorRegistry.insert(std::make_pair(Class->GetClassName(), Creator));
    }
}

Application* AstralEngineStatics::GetApp() {
    return AstralEngineApp;
}

FClass* AstralEngineStatics::GetClass(const std::string& ClassName) {
    return ClassRegistry.at(ClassName);
}

Creator<ABaseObject>* AstralEngineStatics::GetCreator(const FClass* Class) {
    return CreatorRegistry.at(Class->GetClassName());
}

std::vector<FClass*> AstralEngineStatics::GetAllRegistredClasses() {
    std::vector<FClass*> Classes = {};
    for(auto KeyVal : ClassRegistry) {
        Classes.push_back(KeyVal.second);
    }
    return Classes;
}

std::vector<FClass*> AstralEngineStatics::GetAllFactoryClasses() {
    std::vector<FClass*> Classes = {};
    for(auto KeyVal : ClassRegistry) {
        if (CreatorRegistry.contains(KeyVal.second->GetClassName())) {
            Classes.push_back(KeyVal.second);
        }
    }
    return Classes;
}

