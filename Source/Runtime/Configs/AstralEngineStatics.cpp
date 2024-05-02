#include "AstralEngineStatics.h"

#include "../CoreObjects/Entities/Entity.h"
#include "../CoreObjects/Objects/BaseObject.h"
#include "../CoreObjects/ObjectManager.h"
#include "../CoreObjects/Components/Component.h"
#include "../CoreObjects/Components/Implementations/PrimitiveComponent.h"
#include "../CoreObjects/Components/Implementations/SceneComponent.h"
#include "../Engine/Engine.h"
#include "../Engine/Implementations/SFMLEngine.h"
#include "../Inputs/Components/InputComponent.h"
#include "../Inputs/Components/Implementations/SFMLInputComponent.h"
#include "../Inputs/Objects/InputAction.h"
#include "../Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Render/Components/SFML/Implementation/SFMLAnimatedSpriteComponent.h"
#include "../Render/Components/SFML/Implementation/SFMLStaticSpriteComponent.h"
#include "../Render/Systems/RenderManager.h"
#include "../Render/Systems/Implementations/ASFMLRenderManager.h"
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
    REGISTER_ASTRAL_CLASS(ARenderManager)
    REGISTER_ASTRAL_CLASS(ASFMLRenderManager)

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
    REGISTER_ASTRAL_CLASS(AInputAction)
    
    
    //Entities
    REGISTER_ASTRAL_CLASS(AEntity)

    //Components
    REGISTER_ASTRAL_CLASS(AComponent)
    //////////////////////
    REGISTER_ASTRAL_CLASS(ASceneComponent)
    REGISTER_ASTRAL_CLASS(APrimitiveComponent)
    REGISTER_ASTRAL_CLASS(ASFMLSpriteComponent)
    REGISTER_ASTRAL_CLASS(ASFMLStaticSpriteComponent)
    REGISTER_ASTRAL_CLASS(ASFMLAnimatedSpriteComponent)
    //////////////////////
    REGISTER_ASTRAL_CLASS(AInputComponent)
    //REGISTER_ASTRAL_CLASS(ASFMLInputComponent)
}

void AstralEngineStatics::LinkAstralClassesParents() {
    //Managers
    LINK_ASTRAL_CLASS_PARENTS(AObjectManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AInpuManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLInputManager, AInpuManager)
    LINK_ASTRAL_CLASS_PARENTS(ARenderManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLRenderManager, ARenderManager)
    
    //Engines
    LINK_ASTRAL_CLASS_PARENTS(AEngine, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLEngine, AEngine)
    
    //Objects
    ///////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AParserBase, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ABaseStringParser, AParserBase)
    LINK_ASTRAL_CLASS_PARENTS(ABaseBinaryParser, AParserBase)
    LINK_ASTRAL_CLASS_PARENTS(AJsonParser, ABaseStringParser)
    //////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AInputAction, ABaseObject)

    //Entities
    LINK_ASTRAL_CLASS_PARENTS(AEntity, ABaseObject)

    //Components
    LINK_ASTRAL_CLASS_PARENTS(AComponent, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASceneComponent, AComponent)
    LINK_ASTRAL_CLASS_PARENTS(APrimitiveComponent, ASceneComponent)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLSpriteComponent, APrimitiveComponent)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLStaticSpriteComponent, ASFMLSpriteComponent)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLAnimatedSpriteComponent, ASFMLSpriteComponent)
    //////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AInputComponent, AComponent)
    //LINK_ASTRAL_CLASS_PARENTS(ASFMLInputComponent, AInputComponent)
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

TArray<FClass*> AstralEngineStatics::GetAllRegistredClasses() {
    TArray<FClass*> Classes = {};
    for(auto KeyVal : ClassRegistry) {
        Classes.push_back(KeyVal.second);
    }
    return Classes;
}

TArray<FClass*> AstralEngineStatics::GetAllFactoryClasses() {
    TArray<FClass*> Classes = {};
    for(auto KeyVal : ClassRegistry) {
        if (CreatorRegistry.contains(KeyVal.second->GetClassName())) {
            Classes.push_back(KeyVal.second);
        }
    }
    return Classes;
}

