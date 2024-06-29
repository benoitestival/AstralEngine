#include "AstralEngineStatics.h"


#include "../Engine/CoreObjects/ObjectManager.h"
#include "../Engine/CoreObjects/Entities/Entity.h"
#include "../Engine/Engine/Implementations/SFMLEngine.h"
#include "../Engine/Inputs/Components/InputComponent.h"
#include "../Engine/Inputs/Objects/Modifiers/InputModifier.h"
#include "../Engine/Inputs/Objects/Triggers/InputTrigger.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Engine/Time/TimerManager.h"
#include "../Engine/World/World.h"
#include "../Render/Components/SFML/Implementation/SFMLAnimatedSpriteComponent.h"
#include "../Render/Components/SFML/Implementation/SFMLStaticSpriteComponent.h"
#include "../Render/Systems/RenderManager.h"
#include "../Render/Systems/Implementations/ASFMLRenderManager.h"
#include "../Serialization/Parsers/ParserBase.h"


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
    REGISTER_ASTRAL_CLASS(AInputManager)
    REGISTER_ASTRAL_CLASS(ASFMLInputManager)
    REGISTER_ASTRAL_CLASS(ARenderManager)
    REGISTER_ASTRAL_CLASS(ASFMLRenderManager)
    REGISTER_ASTRAL_CLASS(ATimerManager)

    //Engines
    REGISTER_ASTRAL_CLASS(AEngine)
    REGISTER_ASTRAL_CLASS(ASFMLEngine)

    //Objects
    REGISTER_ASTRAL_CLASS(AWorld)
    ///////////////////////
    REGISTER_ASTRAL_PURE_CLASS(AParserBase)
    //REGISTER_ASTRAL_PURE_CLASS(ABaseStringParser)
    //REGISTER_ASTRAL_PURE_CLASS(ABaseBinaryParser)
    //REGISTER_ASTRAL_CLASS(AJsonParser)
    //////////////////////
    REGISTER_ASTRAL_CLASS(AInputAction)
    REGISTER_ASTRAL_CLASS(AInputTrigger)
    REGISTER_ASTRAL_CLASS(AInputModifier)
    ////////////////////
    
    
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
    LINK_ASTRAL_CLASS_PARENTS(AInputManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLInputManager, AInputManager)
    LINK_ASTRAL_CLASS_PARENTS(ARenderManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLRenderManager, ARenderManager)
    LINK_ASTRAL_CLASS_PARENTS(ATimerManager, ABaseObject)
    
    //Engines
    LINK_ASTRAL_CLASS_PARENTS(AEngine, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLEngine, AEngine)
    
    //Objects
    LINK_ASTRAL_CLASS_PARENTS(AWorld, ABaseObject)
    ///////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AParserBase, ABaseObject)
    //LINK_ASTRAL_CLASS_PARENTS(ABaseStringParser, AParserBase)
    //LINK_ASTRAL_CLASS_PARENTS(ABaseBinaryParser, AParserBase)
    //LINK_ASTRAL_CLASS_PARENTS(AJsonParser, ABaseStringParser)
    //////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AInputAction, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AInputTrigger, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AInputModifier, ABaseObject)

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

