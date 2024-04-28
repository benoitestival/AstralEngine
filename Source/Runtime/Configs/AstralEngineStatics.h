#pragma once
#include <string>
#include <unordered_map>

#include "../ReflectionSystem/RTTI.h"
#include "../Utils/Factory.h"

#define REGISTER_ASTRAL_CLASS(Class)\
    if(!AstralEngineStatics::IsClassRegister(#Class)){\
        FClass* Instance##Class = CREATE_RTTI_BASE_CLASS_INSTANCE(Class);\
        AstralEngineStatics::RegisterClass(Instance##Class);\
        AstralEngineStatics::RegisterCreator(Instance##Class, new DerivedCreator<ABaseObject, Class>());\
    }\

#define REGISTER_ASTRAL_NO_FACTORY_CLASS(Class, ...)\
    if(!AstralEngineStatics::IsClassRegister(#Class)){\
        FClass* Instance##Class = CREATE_RTTI_BASE_CLASS_INSTANCE(Class);\
        AstralEngineStatics::RegisterClass(Instance##Class);\
    }\

#define REGISTER_ASTRAL_SINGLETON_CLASS(Class, ...)\
    REGISTER_ASTRAL_NO_FACTORY_CLASS(Class, __VA_ARGS__)

#define REGISTER_ASTRAL_PURE_CLASS(Class, ...)\
    REGISTER_ASTRAL_NO_FACTORY_CLASS(Class, __VA_ARGS__)

#define LINK_ASTRAL_CLASS_PARENTS(Class, ...)\
    Class::StaticClass()->AddParents({VA_ARGS_CODE_EXECUTE(INTERNAL_GET_PARENT_CLASS, __VA_ARGS__)});        

class Application;
struct FClass;

class AstralEngineStatics {
public:
    static void InitAstralEngineStatics(Application* App); 
    static void ClearAstralEngineStatics();

    static void RegisterAstralClasses();
    static void LinkAstralClassesParents();

    static bool IsClassRegister(const std::string& ClassName);
    static bool IsCreatorRegister(const FClass* Class);
    
    static void RegisterClass(FClass* Class);
    static void RegisterCreator(FClass* Class, Creator<ABaseObject>* Creator);

    static Application* GetApp();
    static FClass* GetClass(const std::string& ClassName);
    static Creator<ABaseObject>* GetCreator(const FClass* Class);

    static std::vector<FClass*> GetAllRegistredClasses();
    static std::vector<FClass*> GetAllFactoryClasses();
private:
    static Application* AstralEngineApp ;
    static std::unordered_map<std::string, FClass*> ClassRegistry; 
    static std::unordered_map<std::string, Creator<ABaseObject>*> CreatorRegistry;
};
