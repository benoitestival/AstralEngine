#include "AstralEngineStatics.h"


#include "../../Editor/Tests/DebugMain.h"
#include "../../Editor/Tests/DebugTick.h"
#include "../Engine/CoreObjects/ObjectManager.h"
#include "../Engine/CoreObjects/Components/Implementations/PrimitiveComponent.h"
#include "../Engine/CoreObjects/Components/Implementations/SceneComponent.h"
#include "../Engine/CoreObjects/Entities/Entity.h"
#include "../Engine/Engine/Implementations/AstralEngine.h"
#include "../Engine/Inputs/Components/InputComponent.h"
#include "../Engine/Inputs/Objects/Modifiers/InputModifier.h"
#include "../Engine/Inputs/Objects/Triggers/InputTrigger.h"
#include "../Engine/Inputs/Systems/Implementations/GLFWInputManager.h"
#include "../Engine/Inputs/Systems/Implementations/SFMLInputManager.h"
#include "../Engine/Time/TimerManager.h"
#include "../Engine/World/World.h"
#include "../Render/ShaderSystem/Shader.h"
#include "../Render/ShaderSystem/ShaderManager.h"
#include "../Render/ShaderSystem/Vulkan/VulkanShader.h"
#include "../Render/RenderAPIs/Renderer.h"
#include "../Render/RenderAPIs/Vulkan/VulkanRenderer.h"
#include "../Serialization/Parsers/ParserBase.h"
#include "../Window/Window.h"
#include "../Window/Implementations/GLFWWindow.h"
#include "../Window/Implementations/SFMLWindow.h"


Application* AstralEngineStatics::AstralEngineApp = nullptr;
TMap<std::string, FClass*> AstralEngineStatics::ClassRegistry = {};
TMap<std::string, Creator<ABaseObject>*> AstralEngineStatics::CreatorRegistry = {};

void AstralEngineStatics::InitAstralEngineStatics(Application* App) {
    AstralEngineApp = App;
    RegisterAstralClasses();
    LinkAstralClassesParents();
}

void AstralEngineStatics::ClearAstralEngineStatics() {
    ClassRegistry.Clear();
    CreatorRegistry.Clear();
}

void AstralEngineStatics::RegisterAstralClasses() {
    REGISTER_ASTRAL_CLASS(ABaseObject)

    //Managers
    REGISTER_ASTRAL_CLASS(AManager)
    REGISTER_ASTRAL_SINGLETON_CLASS(AObjectManager)
    REGISTER_ASTRAL_CLASS(AInputManager)
    REGISTER_ASTRAL_CLASS(ASFMLInputManager)
    REGISTER_ASTRAL_CLASS(AOpenGLInputManager)
    REGISTER_ASTRAL_CLASS(AShaderManager)
    REGISTER_ASTRAL_CLASS(ARenderer)
    REGISTER_ASTRAL_CLASS(AVulkanRenderer)
    REGISTER_ASTRAL_CLASS(ATimerManager)

    //Tests
    REGISTER_ASTRAL_CLASS(ADebugMain)
    REGISTER_ASTRAL_CLASS(ADebugTick)
    
    //Engines
    REGISTER_ASTRAL_CLASS(AEngine)
    REGISTER_ASTRAL_CLASS(AstralEngine)

    //Windows
    REGISTER_ASTRAL_CLASS(AWindow)
    REGISTER_ASTRAL_CLASS(ASFMLWindow)
    REGISTER_ASTRAL_CLASS(AGLFWWindow)

    //Render
    REGISTER_ASTRAL_CLASS(AShader)
    REGISTER_ASTRAL_CLASS(AVulkanShader)
    
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
    //////////////////////
    REGISTER_ASTRAL_CLASS(AInputComponent)
    //REGISTER_ASTRAL_CLASS(ASFMLInputComponent)
}

void AstralEngineStatics::LinkAstralClassesParents() {
    //Managers
    LINK_ASTRAL_CLASS_PARENTS(AManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AObjectManager, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AInputManager, AManager)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLInputManager, AInputManager)
    LINK_ASTRAL_CLASS_PARENTS(AOpenGLInputManager, AInputManager)
    LINK_ASTRAL_CLASS_PARENTS(AShaderManager, AManager)
    LINK_ASTRAL_CLASS_PARENTS(ARenderer, AManager)
    LINK_ASTRAL_CLASS_PARENTS(AVulkanRenderer, ARenderer)
    LINK_ASTRAL_CLASS_PARENTS(ATimerManager, AManager)
    
    //Engines
    LINK_ASTRAL_CLASS_PARENTS(AEngine, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AstralEngine, AEngine)

    //Windows
    LINK_ASTRAL_CLASS_PARENTS(AWindow, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ASFMLWindow, AWindow)
    LINK_ASTRAL_CLASS_PARENTS(AGLFWWindow, AWindow)

    //Render
    LINK_ASTRAL_CLASS_PARENTS(AShader, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(AVulkanShader, AShader)
    
    //Objects
    LINK_ASTRAL_CLASS_PARENTS(AWorld, ABaseObject)
    ///////////////////////
    LINK_ASTRAL_CLASS_PARENTS(ADebugMain, ABaseObject)
    LINK_ASTRAL_CLASS_PARENTS(ADebugTick, ABaseObject)
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
    //////////////////////
    LINK_ASTRAL_CLASS_PARENTS(AInputComponent, AComponent)
    //LINK_ASTRAL_CLASS_PARENTS(ASFMLInputComponent, AInputComponent)
}

bool AstralEngineStatics::IsClassRegister(const std::string& ClassName) {
    return ClassRegistry.Contains(ClassName);
}

bool AstralEngineStatics::IsCreatorRegister(const FClass* Class) {
    return CreatorRegistry.Contains(Class->GetClassName());
}

void AstralEngineStatics::RegisterClass(FClass* Class) {
    if (!IsClassRegister(Class->GetClassName())) {
        ClassRegistry.Insert(std::make_pair(Class->GetClassName(), Class));
    }
}

void AstralEngineStatics::RegisterCreator(FClass* Class, Creator<ABaseObject>* Creator) {
    if (!IsCreatorRegister(Class)) {
        CreatorRegistry.Insert(std::make_pair(Class->GetClassName(), Creator));
    }
}

Application* AstralEngineStatics::GetApp() {
    return AstralEngineApp;
}

FClass* AstralEngineStatics::GetClass(const std::string& ClassName) {
    return ClassRegistry.Find(ClassName);
}

Creator<ABaseObject>* AstralEngineStatics::GetCreator(const FClass* Class) {
    return CreatorRegistry.Find(Class->GetClassName());
}

TArray<FClass*> AstralEngineStatics::GetAllRegistredClasses() {
    TArray<FClass*> Classes = {};
    for(auto KeyVal : ClassRegistry) {
        Classes.Add(KeyVal.second);
    }
    return Classes;
}

TArray<FClass*> AstralEngineStatics::GetAllFactoryClasses() {
    TArray<FClass*> Classes = {};
    for(auto KeyVal : ClassRegistry) {
        if (CreatorRegistry.Contains(KeyVal.second->GetClassName())) {
            Classes.Add(KeyVal.second);
        }
    }
    return Classes;
}

